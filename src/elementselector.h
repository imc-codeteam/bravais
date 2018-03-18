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
    QGroupBox* elementbox;
    std::vector<QRadioButton*> radio_buttons;

public:
    explicit ElementSelector(QWidget *parent = 0);

    QString get_selected_element() const;
};

#endif // ELEMENTSELECTOR_H
