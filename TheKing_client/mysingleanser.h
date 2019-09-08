#ifndef MYSINGLEANSER_H
#define MYSINGLEANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "mypaper.h"
#include "myjudge.h"

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

signals://信号

    /*含义：开始答题信号*/
    void do_single_start();

    /*含义：回到主界面信号*/
    void do_MainWindow_show();

    /*含义：再来一次信号*/
    void do_SingleAnser_show();

private slots://槽函数

    /*功能：开始答题*/
    void on_start_Button_clicked();

    /*功能：选择A*/
    void on_A_Button_clicked();

    /*功能：选择B*/
    void on_B_Button_clicked();

    /*功能：选择C*/
    void on_C_Button_clicked();

    /*功能：选择D*/
    void on_D_Button_clicked();

    /*功能：结束答题*/
    void on_End_Button_clicked();

    /*功能：回到主界面*/
    void on_BackButton_clicked();

    /*功能：再来一次*/
    void on_OneMoreButton_clicked();

    /*功能：处理一道题的时间到*/
    void OneTimerUpdate();

public:
    void deal_show();   //恢复控件状态
    void deal_loop();   //延时函数
    void deal_button_result(int);  //响应答题
    void Result();  //答题结束，显示分数/题目数/总时长
    /*功能：线程向客户端传题*/
    void deal_recv_topix(QString,QString,QString,QString,QString,QString);

private:
    MyJudge *judge; //判决

    QTimer* OneTimerId; //每一题的计时器
    int OneTime; //每一题的计时器时间

};

#endif // MYSINGLEANSER_H
