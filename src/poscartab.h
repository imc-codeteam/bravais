#ifndef POSCARTAB_H
#define POSCARTAB_H

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>

class PoscarTab : public QWidget
{
    Q_OBJECT
private:
    QTextEdit* textfield;

public:
    explicit PoscarTab(QWidget *parent = 0);

    void set_content_textfield(const std::string& content);

signals:

public slots:
};

#endif // POSCARTAB_H
