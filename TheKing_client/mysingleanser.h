#ifndef MYSINGLEANSER_H
#define MYSINGLEANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QVector>

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

    QVector topic;
    QVector qA;
    QVector qB;
    QVector qC;
    QVector qD;
    QVector qTrue;

};

#endif // MYSINGLEANSER_H
