/**************************************************************************
 *   This file is part of lanius                                          *
 *   https://github.com/imc-codeteam/lanius                               *
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

#ifndef _SURFACE_CREATOR_H
#define _SURFACE_CREATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <boost/math/common_factor_rt.hpp>
#include <boost/format.hpp>

/**
 * @brief      Class for surface creator.
 */
class SurfaceCreator {
private:
    glm::dmat3 unitcell_bulk;                               //!< bulk unit cell
    glm::dmat3 unitcell_cleaved;                            //!< unit cell of cleaved surface
    glm::dmat3 unitcell_surface;                            //!< unit cell of slab model

    std::vector<glm::dvec3> unitcell_bulk_coordinates;      //!< atom coordinates for bulk unit cell
    std::vector<glm::dvec3> unitcell_cleaved_coordinates;   //!< atom coordinates for cleaved unit cell
    std::vector<glm::dvec3> unitcell_surface_coordinates;   //!< atom coordinates for surface/slab model unit cell

    std::string element;                                    //!< element

public:

    /**
     * @brief      default constructor
     */
    SurfaceCreator();

    /**
     * @brief      constructor unit cell
     *
     * @param[in]  name      crystal structure
     * @param[in]  _element  element
     * @param[in]  a         lattice parameter a
     * @param[in]  b         lattice parameter b
     * @param[in]  c         lattice parameter c
     */
    void construct_unitcell(const std::string& name, const std::string& _element, double a = 0.0, double b = 0.0, double c = 0.0);

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
    void cleave(int h, int k, int l, int a, int b, int c);

    /**
     * @brief      cleave crystal surface
     *
     * @param[in]  vacuum  vacuum height
     */
    void create_surface(double vacuum);

    /**
     * @brief      export surface
     *
     * @param[in]  filename  url to filename
     */
    std::string export_surface();

private:
    /**
     * @brief      construct conventional fcc unit cell
     *
     * @param[in]  a     lattice parameter a
     */
    void construct_fcc(double a);

    /**
     * @brief      construct conventional bcc unit cell
     *
     * @param[in]  a     lattice parameter a
     */
    void construct_bcc(double a);

    /**
     * @brief      construct conventional hcp unit cell
     *
     * @param[in]  a     lattice parameter a
     * @param[in]  b     lattice parameter b
     * @param[in]  c     lattice parameter c
     */
    void construct_hcp(double a, double b, double c);

    /**
     * @brief      find cleave matrix
     *
     * @param[in]  h     miller index h
     * @param[in]  k     miller index k
     * @param[in]  l     miller index l
     *
     * @return     cleave matrix
     */
    glm::dmat3 find_cleave_matrix(int h, int k, int l);

    /**
     * @brief      place all atoms in unit cell and remove duplicates
     *
     * @param      atoms  list of direct coordinates
     */
    void clean_atoms_unitcell(std::vector<glm::dvec3>& atoms);

    /**
     * @brief      extended Euclidean algorithm
     *
     * @param[in]  a     inter a
     * @param[in]  b     inter b
     *
     * @return     pointer to greatest common divisor and coefficients for Bezout's identity
     */
    int *ext_gcd (int a, int b);

    /**
     * @brief      expand unit cell
     *
     * @param[in]  a     repetition in e1 direction
     * @param[in]  b     repetition in e2 direction
     * @param[in]  c     repetition in e3 direction
     */
    void expand_unitcell(int a, int b, int c);

    glm::dmat3 get_rotation_matrix(const glm::dvec3& v1, const glm::dvec3& v2);

    /**
    * @brief      center atom height to unit cell (for building slab model)
    */
    void center_atoms();
};

#endif // _SURFACE_CREATOR_H
