#ifndef MYSINGLEANSER_H
#define MYSINGLEANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QVector>
#include <QThread>
#include "mypaper.h"

//题目数量
#define TitleNum 20

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

signals:
    void do_single_start();
    void do_MainWindow_show();
    void do_SingleAnser_show();

private slots:
    void on_start_Button_clicked();
    void on_A_Button_clicked();
    void on_B_Button_clicked();
    void on_C_Button_clicked();
    void on_D_Button_clicked();
    void on_End_Button_clicked();
    void on_BackButton_clicked();
    void on_OneMoreButton_clicked();

    void deal_single_start(QString,QString,QString,QString,QString,QString);

public:
    void deal_show();   //恢复控件状态
    void deal_loop();   //延时函数
    void deal_button_result();  //响应答题

private:
    QVector<QString> topic;
    QVector<QString> qA;
    QVector<QString> qB;
    QVector<QString> qC;
    QVector<QString> qD;
    QVector<QString> qTrue;

    int TopicNum;    //题目总数量
    int CurrenIndex; //当前题目
    int TrueIndex;   //当前正确答案
    QStringList option ;  //A B C D
    int score;  //得分

};

#endif // MYSINGLEANSER_H
