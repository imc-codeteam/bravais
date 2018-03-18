#include "elementselector.h"

ElementSelector::ElementSelector(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    QGridLayout* grid_layout = new QGridLayout();
    this->elementbox = new QGroupBox();
    this->elementbox->setTitle("Select element");
    this->elementbox->setLayout(grid_layout);
    this->elementbox->setCheckable(false);
    mainLayout->addWidget(this->elementbox);

    // first row transition metals
    this->radio_buttons.push_back(new QRadioButton("Sc"));
    this->radio_buttons.push_back(new QRadioButton("Ti"));
    this->radio_buttons.push_back(new QRadioButton("V"));
    this->radio_buttons.push_back(new QRadioButton("Cr"));
    this->radio_buttons.push_back(new QRadioButton("Mn"));
    this->radio_buttons.push_back(new QRadioButton("Fe"));
    this->radio_buttons.push_back(new QRadioButton("Co"));
    this->radio_buttons.push_back(new QRadioButton("Ni"));
    this->radio_buttons.push_back(new QRadioButton("Cu"));
    this->radio_buttons.push_back(new QRadioButton("Zn"));

    // second row transition metals
    this->radio_buttons.push_back(new QRadioButton("Y"));
    this->radio_buttons.push_back(new QRadioButton("Zr"));
    this->radio_buttons.push_back(new QRadioButton("Nb"));
    this->radio_buttons.push_back(new QRadioButton("Mo"));
    this->radio_buttons.push_back(new QRadioButton("Tc"));
    this->radio_buttons.push_back(new QRadioButton("Ru"));
    this->radio_buttons.push_back(new QRadioButton("Rh"));
    this->radio_buttons.push_back(new QRadioButton("Pd"));
    this->radio_buttons.push_back(new QRadioButton("Ag"));
    this->radio_buttons.push_back(new QRadioButton("Cd"));

    // third row transition metals
    this->radio_buttons.push_back(new QRadioButton("Hf"));
    this->radio_buttons.push_back(new QRadioButton("Ta"));
    this->radio_buttons.push_back(new QRadioButton("W"));
    this->radio_buttons.push_back(new QRadioButton("Re"));
    this->radio_buttons.push_back(new QRadioButton("Os"));
    this->radio_buttons.push_back(new QRadioButton("Ir"));
    this->radio_buttons.push_back(new QRadioButton("Pt"));
    this->radio_buttons.push_back(new QRadioButton("Au"));
    this->radio_buttons.push_back(new QRadioButton("Hg"));

    for(unsigned int i=0; i<10; i++) {
        grid_layout->addWidget(this->radio_buttons[i], 0, i);
    }

    for(unsigned int i=10; i<20; i++) {
        grid_layout->addWidget(this->radio_buttons[i], 1, i-10);
    }

    for(unsigned int i=20; i<29; i++) {
        grid_layout->addWidget(this->radio_buttons[i], 2, i-19);
    }
}

QString ElementSelector::get_selected_element() const {
    for(unsigned int i=0; i<this->radio_buttons.size(); i++) {
        if(this->radio_buttons[i]->isChecked()) {
            return this->radio_buttons[i]->text();
        }
    }

    return "X";
}
