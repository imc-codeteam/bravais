/**************************************************************************
 *   This file is part of Bravais                                         *
 *   https://github.com/imc-codeteam/lanius                               *
 *                                                                        *
 *   Author: Ivo Filot <i.a.w.filot@tue.nl>                               *
 *                                                                        *
 *   Bravais is free software: you can redistribute it and/or modify      *
 *   it under the terms of the GNU General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License,    *
 *   or (at your option) any later version.                               *
 *                                                                        *
 *   Bravais is distributed in the hope that it will be useful,           *
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

    this->set_lattice_parameters(layout);

    this->label_lattice_search_status = new QLabel();
    this->label_lattice_search_status->hide();
    layout->addWidget(this->label_lattice_search_status);

    this->set_miller_index_input(layout);
    this->set_dimensions_input(layout);
    this->set_vacuum_input(layout);

    this->generate_button = new QPushButton();
    this->generate_button->setText("Generate POSCAR");
    this->generate_button->setToolTip("Generate POSCAR file using settings on this tab.");
    layout->addWidget(this->generate_button);

    // connect actions
    connect(this->lattice_list, SIGNAL(currentIndexChanged(const QString&)), this, SLOT (action_on_change_lattice_select(const QString&)));
    connect(this->load_lattice_constants_button, SIGNAL (released()), this, SLOT (action_load_lattice_constants()));
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
 * @brief get the lattice constants
 * @return the lattice constants
 */
std::vector<double> InputTab::get_lattice_constants() const {
    std::vector<double> lattice_const(3, 0.0);

    for(unsigned int i=0; i<3; i++) {
        lattice_const[i] = this->lattice_parameters[i]->value();
    }

    return lattice_const;
}

/**
 * @brief get the miller indices for the crystal cleave
 * @return miller indices
 */
std::vector<int> InputTab::get_miller_indices() const {
    std::vector<int> ans(3, 0);

    for(unsigned int i=0; i<3; i++) {
        ans[i] = this->miller_spinboxes[i]->value();
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
 * @brief build lattice parameter input widgets
 * @param pointer to layout
 */
void InputTab::set_lattice_parameters(QVBoxLayout* layout) {
    QHBoxLayout* lattice_parameters_layout = new QHBoxLayout();
    QWidget* lattice_param_widget = new QWidget();
    lattice_param_widget->setLayout(lattice_parameters_layout);
    layout->addWidget(lattice_param_widget);

    QLabel* miller_index_label = new QLabel("Lattice parameters:");
    lattice_parameters_layout->addWidget(miller_index_label);

    QDoubleSpinBox* lattice_param_a = new QDoubleSpinBox();
    lattice_param_a->setValue(0);
    lattice_param_a->setToolTip("Lattice parameter a");
    lattice_parameters_layout->addWidget(lattice_param_a);

    QDoubleSpinBox* lattice_param_b = new QDoubleSpinBox();
    lattice_param_b->setValue(0);
    lattice_param_b->setToolTip("Lattice parameter b");
    lattice_param_b->hide();
    lattice_parameters_layout->addWidget(lattice_param_b);

    QDoubleSpinBox* lattice_param_c = new QDoubleSpinBox();
    lattice_param_c->setValue(0);
    lattice_param_c->setToolTip("Lattice parameter c");
    lattice_param_c->hide();
    lattice_parameters_layout->addWidget(lattice_param_c);

    // add button to load lattice constants
    this->load_lattice_constants_button = new QPushButton();
    this->load_lattice_constants_button->setText("Load");
    this->load_lattice_constants_button->setToolTip("Try to load lattice parameters from database.");
    lattice_parameters_layout->addWidget(this->load_lattice_constants_button);

    // store pointers
    this->lattice_parameters.push_back(lattice_param_a);
    this->lattice_parameters.push_back(lattice_param_b);
    this->lattice_parameters.push_back(lattice_param_c);
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

/**
 * @brief change the lattice parameter input when you change the lattice
 */
void InputTab::action_on_change_lattice_select(const QString& lattice) {
    if(lattice == "BCC") {
        this->lattice_parameters[0]->show();
        this->lattice_parameters[1]->hide();
        this->lattice_parameters[2]->hide();
    }

    if(lattice == "HCP") {
        this->lattice_parameters[0]->show();
        this->lattice_parameters[1]->hide();
        this->lattice_parameters[2]->show();
    }

    if(lattice == "FCC") {
        this->lattice_parameters[0]->show();
        this->lattice_parameters[1]->hide();
        this->lattice_parameters[2]->hide();
    }

    this->label_lattice_search_status->hide();
}

/**
 * @brief load lattice constants from database
 */
void InputTab::action_load_lattice_constants() {
    // get element
    const std::string element = this->get_element().toUtf8().constData();

    // get lattice
    const std::string lattice = this->get_lattice().toUtf8().constData();

    // build lattice
    CrystalDatabase cdb;
    std::vector<double> lc;

    // try to build the lattice and catch any errors
    try {
        lc = cdb.get_lattice_parameters(element + "-" + lattice);
        this->lattice_parameters[0]->setValue(lc[0]);
        this->lattice_parameters[1]->setValue(lc[1]);
        this->lattice_parameters[2]->setValue(lc[2]);

        this->label_lattice_search_status->setText("Lattice parameters loaded from database");
        this->label_lattice_search_status->show();
    } catch(const std::exception& e) {
        this->label_lattice_search_status->setText(e.what());
        this->label_lattice_search_status->show();
    }
}
