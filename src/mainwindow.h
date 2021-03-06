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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <QTabWidget>

#include <iostream>

#include "poscartab.h"
#include "inputtab.h"
#include "surface_creator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTabWidget *tabs;
    InputTab *input_tab;
    PoscarTab* poscar_tab;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void action_build_unit_cell();

    void action_save_poscar();

private:
    void create_tabs();
};

#endif // MAINWINDOW_H
