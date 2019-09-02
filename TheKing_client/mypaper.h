#ifndef MYPAPER_H
#define MYPAPER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>

namespace Ui {
class MyPaper;
}

class MyPaper : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyPaper(QWidget *parent = 0);
    ~MyPaper();

private:
    Ui::MyPaper *ui;
};

#endif // MYPAPER_H
