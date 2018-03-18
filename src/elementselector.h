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

#ifndef ELEMENTSELECTOR_H
#define ELEMENTSELECTOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>

class ElementSelector : public QWidget
{
    Q_OBJECT
private:
    QGroupBox* elementbox;						// group box
    std::vector<QRadioButton*> radio_buttons;	// radio buttons for all elements

public:

    /**
     * @brief      constructor
     *
     * @param      parent  parent widget
     */
    explicit ElementSelector(QWidget *parent = 0);

    /**
	 * @brief      get the selected element
	 *
	 * @return     the selected element
	 */
    QString get_selected_element() const;
};

#endif // ELEMENTSELECTOR_H
