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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);

    // create tabs
    this->create_tabs();

    // create vertical layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(5);
    layout->addWidget(this->tabs);
    widget->setLayout(layout);  

    // display status message
    statusBar()->showMessage(tr("Welcome to Bravais editor"));

    // set window parameters
    this->setWindowTitle("Bravais Crystal Builder");    // set window label
    this->setMinimumSize(600, 400);                     // set minimum size of the window
    this->resize(600, 600);                             // resize the windows

    // connect signals
    connect(this->input_tab->get_generate_button(), SIGNAL (released()), this, SLOT (action_build_unit_cell()));
    connect(this->poscar_tab->get_save_button(), SIGNAL (released()), this, SLOT (action_save_poscar()));
}

void MainWindow::create_tabs() {
    this->tabs = new QTabWidget();
    this->input_tab = new InputTab();
    this->poscar_tab = new PoscarTab();
    this->tabs->addTab(this->input_tab, tr("Input"));
    this->tabs->addTab(this->poscar_tab, tr("Poscar"));
}

void MainWindow::action_build_unit_cell() {
    // start obtaining data

    // get element
    const std::string element = this->input_tab->get_element().toUtf8().constData();

    // get lattice
    const std::string lattice = this->input_tab->get_lattice().toUtf8().constData();

    // get miller indices
    std::vector<int> miller_indices = this->input_tab->get_miller_indices();

    // get cell dimensions
    std::vector<int> cell_dimensions = this->input_tab->get_cell_dimensions();

    // get vacuum thickness
    const double vacuum = this->input_tab->get_vacuum_thickness();

    // build lattice
    SurfaceCreator sf;
    CrystalDatabase cdb;
    std::vector<double> lc;

    // try to build the lattice and catch any errors
    try {
        lc = cdb.get_lattice_parameters(element + "-" + lattice);
        sf.construct_unitcell(lattice, element, lc[0], lc[1], lc[2]);
        sf.cleave(miller_indices[0], miller_indices[1], miller_indices[2], cell_dimensions[0], cell_dimensions[1], cell_dimensions[2]);
        sf.create_surface(vacuum);

        std::string content = sf.export_surface();
        this->poscar_tab->set_content_textfield(content);

        statusBar()->showMessage(tr("Structure succesfully generated"));
        statusBar()->setStyleSheet("QStatusBar{padding-left:8px;background:rgba(0,255,0,255);color:black;font-weight:bold;}");
    } catch(const std::exception& e) {
        statusBar()->showMessage(tr(e.what()));
        statusBar()->setStyleSheet("QStatusBar{padding-left:8px;background:rgba(255,0,0,255);color:black;font-weight:bold;}");
    }
}

void MainWindow::action_save_poscar() {
    QString fname = QFileDialog::getSaveFileName(this,
            tr("Save POSCAR file"), "",
            tr("All Files (*)"));

    std::string filename = fname.toUtf8().constData();
    std::string content = this->poscar_tab->get_textfield()->toPlainText().toUtf8().constData();

    std::ofstream outfile(filename);
    outfile << content;
    outfile.close();

    statusBar()->showMessage(tr("Contents succesfully saved"));
    statusBar()->setStyleSheet("QStatusBar{padding-left:8px;background:rgba(0,255,0,255);color:black;font-weight:bold;}");
}

MainWindow::~MainWindow(){}
