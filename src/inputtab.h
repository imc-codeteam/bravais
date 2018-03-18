#ifndef INPUTTAB_H
#define INPUTTAB_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "elementselector.h"
#include "unitcellbuilder.h"

class InputTab : public QWidget
{
    Q_OBJECT

private:
    QComboBox* lattice_list;
    ElementSelector* element_selector;

    std::vector<QSpinBox*> miller_spinboxes;
    std::vector<QSpinBox*> dimensions_spinboxes;
    QDoubleSpinBox* vacuum_spinbox;

    QPushButton* generate_button;

public:
    explicit InputTab(QWidget *parent = 0);

    inline QPushButton* get_generate_button() const {
        return this->generate_button;
    }

    QString get_element() const;

    QString get_lattice() const;

    std::vector<int> get_miller_indices() const;

    std::vector<int> get_cell_dimensions() const;

    double get_vacuum_thickness() const;

private:
    void set_lattice_input(QVBoxLayout* layout);
    void set_miller_index_input(QVBoxLayout* layout);
    void set_dimensions_input(QVBoxLayout* layout);
    void set_vacuum_input(QVBoxLayout* layout);
};

#endif // INPUTTAB_H
