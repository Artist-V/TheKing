#ifndef MYREG_H
#define MYREG_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMovie>

namespace Ui {
class MyReg;
}

class MyReg : public QWidget
{
    Q_OBJECT

public:
    explicit MyReg(QWidget *parent = 0);
    ~MyReg();

private:
    Ui::MyReg *ui;
    QMovie *movie;
};

#endif // MYREG_H
