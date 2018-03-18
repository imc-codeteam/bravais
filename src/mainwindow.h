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
#include "crystal_database.h"

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

private:
    void create_tabs();
};

#endif // MAINWINDOW_H
