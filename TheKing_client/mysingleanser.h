#ifndef MYSINGLEANSER_H
#define MYSINGLEANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>

namespace Ui {
class MySingleAnser;
}

class MySingleAnser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MySingleAnser(QWidget *parent = 0);
    ~MySingleAnser();

private:
    Ui::MySingleAnser *ui;
};

#endif // MYSINGLEANSER_H
