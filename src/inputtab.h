/**************************************************************************
 *   This file is part of Bravais                                         *
 *   https://github.com/imc-codeteam/bravais                              *
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

#ifndef INPUTTAB_H
#define INPUTTAB_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "elementselector.h"

/**
 * @brief The InputTab class
 */
class InputTab : public QWidget
{
    Q_OBJECT

private:
    QComboBox* lattice_list;                        // list of lattices
    ElementSelector* element_selector;              // widget to select element

    std::vector<QSpinBox*> miller_spinboxes;        // widget to set miller indices
    std::vector<QSpinBox*> dimensions_spinboxes;    // widget to set unit cell dimensions
    QDoubleSpinBox* vacuum_spinbox;                 // set vacuum thickness

    QPushButton* generate_button;                   // button to generate poscar file

public:

    /**
     * @brief Input tab constructor
     * @param parent widget
     */
    explicit InputTab(QWidget *parent = 0);

    /**
     * @brief get pointer to generate button (necessary for connecting signal)
     * @return
     */
    inline QPushButton* get_generate_button() const {
        return this->generate_button;
    }

    /**
     * @brief get the element name (i.e. Co, Ru...)
     * @return element name
     */
    QString get_element() const;

    /**
     * @brief get the lattice type (i.e. FCC, BCC, HCP)
     * @return lattice type
     */
    QString get_lattice() const;

    /**
     * @brief get the miller indices for the crystal cleave
     * @return miller indices
     */
    std::vector<int> get_miller_indices() const;

    /**
     * @brief get the cell dimensions
     * @return cell dimensions
     */
    std::vector<int> get_cell_dimensions() const;

    /**
     * @brief get the vacuum thickness
     * @return vacuum thickness
     */
    double get_vacuum_thickness() const;

private:
    /**
     * @brief build miller indices input widgets
     * @param pointer to layout
     */
    void set_miller_index_input(QVBoxLayout* layout);

    /**
     * @brief build dimension input widgets
     * @param pointer to layout
     */
    void set_dimensions_input(QVBoxLayout* layout);

    /**
     * @brief build vacuum thickness widgets
     * @param pointer to layout
     */
    void set_vacuum_input(QVBoxLayout* layout);
};

#endif // INPUTTAB_H
