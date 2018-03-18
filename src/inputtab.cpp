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

#include "inputtab.h"

/**
 * @brief Input tab constructor
 * @param parent widget
 */
InputTab::InputTab(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    // add a ScrollArea widget and define properties
    QScrollArea *scrollArea = new QScrollArea(this);     //Create scroll area Widget
    scrollArea->viewport()->setBackgroundRole(QPalette::Dark); //Give background color
    scrollArea->viewport()->setAutoFillBackground(true); //
    scrollArea->setContentsMargins(0,0,0,0);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    scrollArea->setWidgetResizable(true);

    // add ScrollArea to QWidget
    mainLayout->addWidget(scrollArea);

    // create new Widget for in the QScrollArea and set properties
    QWidget* widget = new QWidget();
    widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    // add Widget to ScrollArea
    scrollArea->setWidget(widget);

    QVBoxLayout *layout = new QVBoxLayout;
    widget->setLayout(layout);

    this->element_selector = new ElementSelector();
    layout->addWidget(this->element_selector);

    this->lattice_list = new QComboBox();
    this->lattice_list->addItem(tr("BCC"));
    this->lattice_list->addItem(tr("FCC"));
    this->lattice_list->addItem(tr("HCP"));
    this->lattice_list->setCurrentIndex(1);
    layout->addWidget(this->lattice_list);

    this->set_miller_index_input(layout);
    this->set_dimensions_input(layout);
    this->set_vacuum_input(layout);

    this->generate_button = new QPushButton();
    this->generate_button->setText("Generate POSCAR");
    layout->addWidget(this->generate_button);
}

/**
 * @brief get the element name (i.e. Co, Ru...)
 * @return element name
 */
QString InputTab::get_element() const {
    return this->element_selector->get_selected_element();
}

/**
 * @brief get the lattice type (i.e. FCC, BCC, HCP)
 * @return lattice type
 */
QString InputTab::get_lattice() const {
    return this->lattice_list->currentText();
}

/**
 * @brief get the miller indices for the crystal cleave
 * @return miller indices
 */
std::vector<int> InputTab::get_miller_indices() const {
    std::vector<int> ans;

    for(unsigned int i=0; i<3; i++) {
        ans.push_back(this->miller_spinboxes[i]->value());
    }

    return ans;
}

/**
 * @brief get the cell dimensions
 * @return cell dimensions
 */
std::vector<int> InputTab::get_cell_dimensions() const {
    std::vector<int> ans;

    for(unsigned int i=0; i<3; i++) {
        ans.push_back(this->dimensions_spinboxes[i]->value());
    }

    return ans;
}

/**
 * @brief get the vacuum thickness
 * @return vacuum thickness
 */
double InputTab::get_vacuum_thickness() const {
    return this->vacuum_spinbox->value();
}

/**
 * @brief build miller indices input widgets
 * @param pointer to layout
 */
void InputTab::set_miller_index_input(QVBoxLayout* layout) {
    QHBoxLayout* miller_indices_layout = new QHBoxLayout();
    QWidget* miller_indices = new QWidget();
    miller_indices->setLayout(miller_indices_layout);
    layout->addWidget(miller_indices);

    QLabel* miller_index_label = new QLabel("Miller indices:");
    miller_indices_layout->addWidget(miller_index_label);

    QSpinBox* miller_index_h = new QSpinBox();
    miller_index_h->setValue(1);
    miller_indices_layout->addWidget(miller_index_h);

    QSpinBox* miller_index_k = new QSpinBox();
    miller_index_k->setValue(1);
    miller_indices_layout->addWidget(miller_index_k);

    QSpinBox* miller_index_l = new QSpinBox();
    miller_index_l->setValue(1);
    miller_indices_layout->addWidget(miller_index_l);

    // store pointers
    this->miller_spinboxes.push_back(miller_index_h);
    this->miller_spinboxes.push_back(miller_index_k);
    this->miller_spinboxes.push_back(miller_index_l);
}

/**
 * @brief build dimension input widgets
 * @param pointer to layout
 */
void InputTab::set_dimensions_input(QVBoxLayout* layout) {
    QHBoxLayout* dimensions_layout = new QHBoxLayout();
    QWidget* dimensions = new QWidget();
    dimensions->setLayout(dimensions_layout);
    layout->addWidget(dimensions);

    QLabel* miller_index_label = new QLabel("Dimensions:");
    dimensions_layout->addWidget(miller_index_label);

    QSpinBox* dimensions_a = new QSpinBox();
    dimensions_a->setValue(1);
    dimensions_layout->addWidget(dimensions_a);

    QSpinBox* dimensions_b = new QSpinBox();
    dimensions_b->setValue(1);
    dimensions_layout->addWidget(dimensions_b);

    QSpinBox* dimensions_c = new QSpinBox();
    dimensions_c->setValue(1);
    dimensions_layout->addWidget(dimensions_c);

    // store pointers
    this->dimensions_spinboxes.push_back(dimensions_a);
    this->dimensions_spinboxes.push_back(dimensions_b);
    this->dimensions_spinboxes.push_back(dimensions_c);
}

/**
 * @brief build vacuum thickness widgets
 * @param pointer to layout
 */
void InputTab::set_vacuum_input(QVBoxLayout* layout) {
    QHBoxLayout* vacuum_layout = new QHBoxLayout();
    QWidget* vacuum = new QWidget();
    vacuum->setLayout(vacuum_layout);
    layout->addWidget(vacuum);

    QLabel* vacuum_label = new QLabel("Vacuum thickness:");
    vacuum_layout->addWidget(vacuum_label);

    this->vacuum_spinbox = new QDoubleSpinBox();
    this->vacuum_spinbox->setValue(15.0);
    vacuum_layout->addWidget(this->vacuum_spinbox);
}
