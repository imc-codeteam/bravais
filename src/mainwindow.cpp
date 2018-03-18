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
    QString message = tr("Welcome to Bravais editor");
    statusBar()->showMessage(message);

    // set window parameters
    this->setWindowTitle("Bravais Crystal Builder");    // set window label
    this->setMinimumSize(600, 400);                     // set minimum size of the window
    this->resize(600, 600);                             // resize the windows

    // connect signals
    connect(this->input_tab->get_generate_button(), SIGNAL (released()), this, SLOT (action_build_unit_cell()));
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
    const std::vector<double> lc = cdb.get_lattice_parameters(element + "-" + lattice);
    sf.construct_unitcell(lattice, element, lc[0], lc[1], lc[2]);
    sf.cleave(miller_indices[0], miller_indices[1], miller_indices[2], cell_dimensions[0], cell_dimensions[1], cell_dimensions[2]);
    sf.create_surface(vacuum);

    std::string content = sf.export_surface();
    this->poscar_tab->set_content_textfield(content);
}

MainWindow::~MainWindow()
{
}
