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

#include "poscartab.h"

/**
 * @brief Tab for POSCAR file
 * @param parent widget
 */
PoscarTab::PoscarTab(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    this->textfield = new QTextEdit();
    mainLayout->addWidget(this->textfield);

    this->save_button = new QPushButton();
    this->save_button->setText("Save");
    mainLayout->addWidget(this->save_button);
}

/**
 * @brief set contents for POSCAR text field
 * @param contents
 */
void PoscarTab::set_content_textfield(const std::string& content) {
    QString qstr = QString::fromStdString(content);
    this->textfield->setText(qstr);
}
