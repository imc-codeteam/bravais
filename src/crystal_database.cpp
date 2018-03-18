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

#include "crystal_database.h"

/**
 * @brief      Constructs the object.
 */
CrystalDatabase::CrystalDatabase() {
    // 27 - Cobalt
    this->crystals.emplace("Co-FCC", std::vector<double>({3.54, 3.54, 3.54}));
    this->crystals.emplace("Co-HCP", std::vector<double>({2.50, 2.50, 4.06}));

    // 44 - Ruthenium
    this->crystals.emplace("Ru-HCP", std::vector<double>({2.70, 2.70, 4.28}));

    // 47 - Silver
    this->crystals.emplace("Ag-FCC", std::vector<double>({4.08, 4.08, 4.08}));
}

/**
 * @brief      get lattice parameters from metal and crystal
 *
 * @param[in]  name  pattern name
 *
 * @return     The lattice parameters.
 */
const std::vector<double>& CrystalDatabase::get_lattice_parameters(const std::string name) {
    auto got = this->crystals.find(name);
    if(got != this->crystals.end()) {
        return got->second;
    } else {
        throw std::runtime_error("Could not find crystal with pattern: " + name);
    }
}
