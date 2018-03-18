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

#ifndef _CRYSTAL_DATABASE_H
#define _CRYSTAL_DATABASE_H

#include <vector>
#include <string>
#include <unordered_map>

/**
 * @brief      Class for crystal database.
 */
class CrystalDatabase {
private:
    std::unordered_map<std::string, std::vector<double> > crystals; //!< database of crystal lattice parameters

public:

    /**
     * @brief      Constructs the object.
     */
    CrystalDatabase();

    /**
     * @brief      get lattice parameters from metal and crystal
     *
     * @param[in]  name  pattern name
     *
     * @return     The lattice parameters.
     */
    const std::vector<double>& get_lattice_parameters(const std::string name);

private:
};

#endif // _CRYSTAL_DATABASE_H
