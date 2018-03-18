/**************************************************************************
 *   CMakeLists.txt  --  This file is part of lanius.                     *
 *                                                                        *
 *   Author: Ivo Filot <i.a.w.filot@tue.nl>                               *
 *                                                                        *
 *   lanius is free software: you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License,    *
 *   or (at your option) any later version.                               *
 *                                                                        *
 *   lanius is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#include "surface_creator.h"

/**
 * @brief      default constructor
 */
SurfaceCreator::SurfaceCreator() {}

/**
 * @brief      constructor unit cell
 *
 * @param[in]  name      crystal structure
 * @param[in]  _element  element
 * @param[in]  a         lattice parameter a
 * @param[in]  b         lattice parameter b
 * @param[in]  c         lattice parameter c
 */
void SurfaceCreator::construct_unitcell(const std::string& name, const std::string& _element, double a, double b, double c) {
    this->element = _element;

    if(name.compare("FCC") == 0) {
        this->construct_fcc(a);
        return;
    }

    if(name.compare("HCP") == 0) {
        this->construct_hcp(a,a,c);
        return;
    }

    if(name.compare("BCC") == 0) {
        this->construct_bcc(a);
        return;
    }

    throw std::runtime_error("Unsupported or invalid lattice type encountered: " + name);
}

/**
 * @brief      cleave crystal surface
 *
 * @param[in]  h     h miller index
 * @param[in]  k     k miller index
 * @param[in]  l     l miller index
 * @param[in]  a     repetition in e1 direction
 * @param[in]  b     repetition in e2 direction
 * @param[in]  c     repetition in e3 direction (height)
 */
void SurfaceCreator::cleave(int h, int k, int l, int a, int b, int c) {
    // find unitcell matrix after surface cleavage
    this->unitcell_cleaved = this->unitcell_bulk * this->find_cleave_matrix(h, k, l);

    // perform basis transformation on atoms
    const glm::dmat3 rotmat = glm::inverse(this->unitcell_cleaved) * this->unitcell_bulk;
    for(unsigned int i=0; i<this->unitcell_bulk_coordinates.size(); i++) {
        this->unitcell_cleaved_coordinates.push_back(rotmat * unitcell_bulk_coordinates[i]);
    }

    // reduce the atoms to the plane
    this->clean_atoms_unitcell(this->unitcell_cleaved_coordinates);

    // expand unitcell
    this->expand_unitcell(a, b, c);
}

/**
 * @brief      cleave crystal surface
 *
 * @param[in]  vacuum  vacuum height
 */
void SurfaceCreator::create_surface(double vacuum) {
    // get individual vectors from cleaved unitcell matrix
    const glm::dvec3 a1 = glm::column(this->unitcell_cleaved, 0);
    const glm::dvec3 a2 = glm::column(this->unitcell_cleaved, 1);
    const glm::dvec3 a3 = glm::column(this->unitcell_cleaved, 2);

    // construct interim unit cell
    const glm::dvec3 d1 = a1;
    const glm::dvec3 d2 = a2;
    const glm::dvec3 cc = glm::cross(a1, a2);
    const double ll = glm::length(cc);
    const glm::dvec3 d3 = cc * glm::dot(a3, cc) / (ll * ll);    // establish z-vector
    const glm::dmat3 intmat = glm::dmat3(d1, d2, d3);

    // reposition atoms in the new unit cell
    glm::dmat3 tmat = glm::inverse(intmat) * this->unitcell_cleaved;
    for(unsigned int i=0; i<this->unitcell_cleaved_coordinates.size(); i++) {
        this->unitcell_surface_coordinates.push_back(tmat * this->unitcell_cleaved_coordinates[i]);
    }

    // ensure that all atoms lie within the unit cell
    #pragma omp parallel for
    for(unsigned int i=0; i<this->unitcell_surface_coordinates.size(); i++) {
        this->unitcell_surface_coordinates[i] = glm::fract(this->unitcell_surface_coordinates[i]);
        for(unsigned int j=0; j<3; j++) {
            if(std::fabs(this->unitcell_surface_coordinates[i][j] - 1.0) < 1e-5) {
                this->unitcell_surface_coordinates[i][j] = 0.0;
            }
        }
    }

    // construct final unit cell where first two vectors are aligned with xy-plane
    const glm::dvec3 c1 = glm::dvec3(glm::length(d1), 0.0, 0.0);
    const double proj = glm::dot(d1, d2) / glm::length(d1);
    const double l = glm::length(d2);
    const glm::dvec3 c2 = glm::dvec3(proj,
                                     std::sqrt((l * l) - (proj * proj)),
                                     0.0);
    const glm::dvec3 c3 = glm::dvec3(0.0, 0.0, glm::length(d3));
    const glm::dmat3 surf_novac = glm::dmat3(c1, c2, c3);

    // create unit cell with larger height to accomodate vacuum
    this->unitcell_surface = glm::dmat3(c1, c2, c3 + glm::dvec3(0,0,vacuum));

    // reposition atoms in larger unit cell (scale z-position)
    tmat = glm::inverse(this->unitcell_surface) * surf_novac;
    #pragma omp parallel for
    for(unsigned int i=0; i<this->unitcell_surface_coordinates.size(); i++) {
        this->unitcell_surface_coordinates[i] = glm::fract(tmat * this->unitcell_surface_coordinates[i]);
        for(unsigned int j=0; j<3; j++) {
            if(std::fabs(this->unitcell_surface_coordinates[i][j] - 1.0) < 1e-5) {
                this->unitcell_surface_coordinates[i][j] = 0.0;
            }
        }
    }

    // center all atoms so that the slab lies in the middle of the unit cell
    this->center_atoms();
}

/**
 * @brief      export surface
 *
 * @param[in]  filename  url to filename
 */
std::string SurfaceCreator::export_surface() {
    std::stringstream out;

    out << "Plane" << std::endl;
    out << "1.0" << std::endl;
    for(unsigned int i=0; i<3; i++) {
        out << boost::format("%12.6f  %12.6f  %12.6f") % this->unitcell_surface[i][0] % this->unitcell_surface[i][1] % this->unitcell_surface[i][2] << std::endl;
    }
    out << "  " << this->element << std::endl;
    out << "  " << this->unitcell_surface_coordinates.size() << std::endl;
    out << "Direct" << std::endl;
    for(unsigned int i=0; i<this->unitcell_surface_coordinates.size(); i++) {
        out << boost::format("%12.6f  %12.6f  %12.6f") % this->unitcell_surface_coordinates[i][0] % this->unitcell_surface_coordinates[i][1] % this->unitcell_surface_coordinates[i][2] << std::endl;
    }

    return out.str();
}

/**
 * @brief      construct conventional fcc unit cell
 *
 * @param[in]  a     lattice parameter a
 */
void SurfaceCreator::construct_fcc(double a) {
    this->unitcell_bulk[0][0] = a;
    this->unitcell_bulk[1][1] = a;
    this->unitcell_bulk[2][2] = a;

    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0,0,0));
    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0.5,0.5,0));
    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0.5,0,0.5));
    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0,0.5,0.5));
}

/**
 * @brief      construct conventional bcc unit cell
 *
 * @param[in]  a     lattice parameter a
 */
void SurfaceCreator::construct_bcc(double a) {
    this->unitcell_bulk[0][0] = a;
    this->unitcell_bulk[1][1] = a;
    this->unitcell_bulk[2][2] = a;

    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0,0,0));
    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0.5,0.5,0.5));
}

/**
 * @brief      construct conventional hcp unit cell
 *
 * @param[in]  a     lattice parameter a
 * @param[in]  b     lattice parameter b
 * @param[in]  c     lattice parameter c
 */
void SurfaceCreator::construct_hcp(double a, double b, double c) {
    this->unitcell_bulk[0][0] = a;
    this->unitcell_bulk[1][0] = -0.5 * a;
    this->unitcell_bulk[1][1] = std::sqrt(3.0) / 2.0 * a;
    this->unitcell_bulk[2][2] = c;

    this->unitcell_bulk_coordinates.push_back(glm::dvec3(0,0,0));
    this->unitcell_bulk_coordinates.push_back(glm::dvec3(1.0 / 3.0, 2.0 / 3.0, 0.5));
}

/**
 * @brief      expand unit cell
 *
 * @param[in]  a     repetition in e1 direction
 * @param[in]  b     repetition in e2 direction
 * @param[in]  c     repetition in e3 direction
 */
void SurfaceCreator::expand_unitcell(int a, int b, int c) {
    // create more atoms according to expansion
    size_t ln = this->unitcell_cleaved_coordinates.size();
    for(int z=0; z<c; z++) {
        for(int y=0; y<b; y++) {
            for(int x=0; x<a; x++) {
                if(!(x == 0 && y == 0 && z == 0)) {
                    for(unsigned int l=0; l<ln; l++) {
                        this->unitcell_cleaved_coordinates.push_back(
                                this->unitcell_cleaved_coordinates[l] + glm::dvec3((double)x, (double)y, (double)z)
                            );
                    }
                }
            }
        }
    }

    // construct new expanded unitcell matrix
    glm::dmat3 newmat = this->unitcell_cleaved;
    for(unsigned int i=0; i<3; i++) {
        newmat[0][i] *= (double)a;
        newmat[1][i] *= (double)b;
        newmat[2][i] *= (double)c;
    }

    // perform basis transformation
    const glm::dmat3 tmat = glm::inverse(newmat) * this->unitcell_cleaved;
    #pragma omp parallel for
    for(unsigned int i=0; i<this->unitcell_cleaved_coordinates.size(); i++) {
        this->unitcell_cleaved_coordinates[i] = tmat * this->unitcell_cleaved_coordinates[i];
    }

    // store new unitcell matrix
    this->unitcell_cleaved = newmat;
}

/**
 * @brief      place all atoms in unit cell and remove duplicates
 *
 * @param      atoms  list of direct coordinates
 */
void SurfaceCreator::clean_atoms_unitcell(std::vector<glm::dvec3>& atoms) {
    #pragma omp parallel for
    for(unsigned int i=0; i<atoms.size(); i++) {
        atoms[i] = glm::fract(atoms[i]);
        for(unsigned int j=0; j<3; j++) {
            atoms[i][j] -= std::floor(atoms[i][j] + 1e-10);
        }
    }

    // remove duplicates
    std::vector<glm::dvec3> reduced_coord;
    for(unsigned int i=0; i<atoms.size(); i++) {
        bool duplicate = false;
        for(int j=i-1; j>=0; j--) {
            if(glm::distance(atoms[i], atoms[j]) < 1e-10) {
                duplicate = true;
                break;
            }
        }
        if(!duplicate) {
            reduced_coord.push_back(atoms[i]);
        }
    }

    atoms = reduced_coord;
}

/**
 * @brief      find cleave matrix
 *
 * @param[in]  h     miller index h
 * @param[in]  k     miller index k
 * @param[in]  l     miller index l
 *
 * @return     cleave matrix
 */
glm::dmat3 SurfaceCreator::find_cleave_matrix(int h, int k, int l) {
    // early exit is two digits are zero
    if(h == 0 && k == 0) {
        return glm::dmat3(glm::dvec3(1,0,0), glm::dvec3(0,1,0), glm::dvec3(0,0,1));
    }

    if(h == 0 && l == 0) {
        return glm::dmat3(glm::dvec3(0,0,1), glm::dvec3(1,0,0), glm::dvec3(0,1,0));
    }

    if(k == 0 && l == 0) {
        return glm::dmat3(glm::dvec3(0,1,0), glm::dvec3(0,0,1), glm::dvec3(1,0,0));
    }

    // continue working if not
    int* pq = this->ext_gcd(k,l);
    double p = (double)pq[0];
    double q = (double)pq[1];
    delete pq;

    const glm::dvec3 a1 = glm::column(this->unitcell_bulk, 0);
    const glm::dvec3 a2 = glm::column(this->unitcell_bulk, 1);
    const glm::dvec3 a3 = glm::column(this->unitcell_bulk, 2);

    const double k1 = glm::dot(p * ((double)k * a1 - (double)h * a2) + q * ((double)l * a1 - (double)h * a3), (double)l * a2 - (double)k * a3);
    const double k2 = glm::dot((double)l * ((double)k * a1 - (double)h * a2) - (double)k * ((double)l * a1 - (double)h * a3), (double)l * a2 - (double)k * a3);

    if(std::fabs(k2) > 1e-10) {
        const double i = -std::round(k1 / k2);  // i corresponding to the optimal basis
        p += i * l;
        q -= i * k;
    }

    int* ab = this->ext_gcd(p * k + q * l, h);
    const double a = (double)ab[0];
    const double b = (double)ab[1];
    delete ab;

    const glm::dvec3 c1 = glm::dvec3(p * (double)k + q * (double)l, -p * (double)h, -q * (double)h);
    const glm::dvec3 c2 = glm::dvec3(0, (double)l, -(double)k) / (double)boost::math::gcd(l,k);
    const glm::dvec3 c3 = glm::dvec3(b, a * p, a * q);

    return glm::dmat3(c1, c2, c3);
}

/**
 * @brief      extended Euclidean algorithm
 *
 * @param[in]  a     inter a
 * @param[in]  b     inter b
 *
 * @return     pointer to greatest common divisor and coefficients for Bezout's identity
 */
int *SurfaceCreator::ext_gcd (int a, int b){
    int* ans = (int *)malloc(sizeof(int) * 2);

    if(b == 0) {
        ans[0] = 1;
        ans[1] = 0;
        return ans;
    } else if(a % b == 0) {
        ans[0] = 0;
        ans[1] = 1;
        return ans;
    } else {
        int* aa = ext_gcd(b, a % b);
        ans[0] = aa[1];
        ans[1] = aa[0] - aa[1] * (a / b);
        delete aa;
        return ans;
    }
}

/**
 * @brief      center atom height to unit cell (for building slab model)
 */
void SurfaceCreator::center_atoms() {
    // calculate center height
    double ctr = 0.0;
    #pragma omp parallel for reduction(+:ctr)
    for(unsigned int i=0; i<this->unitcell_surface_coordinates.size(); i++) {
        ctr += this->unitcell_surface_coordinates[i][2];
    }

    // correct all atoms with this height
    ctr /= (double)this->unitcell_surface_coordinates.size();
    #pragma omp parallel for
    for(unsigned int i=0; i<this->unitcell_surface_coordinates.size(); i++) {
        this->unitcell_surface_coordinates[i][2] -= ctr - 0.5;
    }
}
