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

#ifndef POSCARTAB_H
#define POSCARTAB_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

#include <fstream>

class PoscarTab : public QWidget
{
    Q_OBJECT
private:
    QTextEdit* textfield;       // pointer to textfield
    QPushButton* save_button;   // pointer to save button

public:
    /**
     * @brief Tab for POSCAR file
     * @param parent widget
     */
    explicit PoscarTab(QWidget *parent = 0);

    /**
     * @brief set contents for POSCAR text field
     * @param contents
     */
    void set_content_textfield(const std::string& content);

    /**
     * @brief get pointer to text field (needed for executing action)
     * @return pointer to QTextEdit object
     */
    inline QTextEdit* get_textfield() const {
        return this->textfield;
    }

    /**
     * @brief get pointer to save button (needed for connecting action)
     * @return pointer to QPushButton object
     */
    inline QPushButton* get_save_button() const {
        return this->save_button;
    }

signals:

public slots:

};

#endif // POSCARTAB_H
