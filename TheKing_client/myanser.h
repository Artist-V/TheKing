#ifndef MYANSER_H
#define MYANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "mypaper.h"

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

public:
    void deal_show();
    void deal_loop();
    void deal_button_result();
};

#endif // MYANSER_H
