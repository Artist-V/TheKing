#ifndef MYANSER_H
#define MYANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>

namespace Ui {
class MyAnser;
}

class MyAnser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyAnser(QWidget *parent = 0);
    ~MyAnser();

private:
    Ui::MyAnser *ui;
};

#endif // MYANSER_H
