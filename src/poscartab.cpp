#include "poscartab.h"

PoscarTab::PoscarTab(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    this->textfield = new QTextEdit();
    mainLayout->addWidget(this->textfield);
}

void PoscarTab::set_content_textfield(const std::string& content) {
    QString qstr = QString::fromStdString(content);
    this->textfield->setText(qstr);
}
