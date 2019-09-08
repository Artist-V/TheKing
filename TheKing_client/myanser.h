#ifndef MYANSER_H
#define MYANSER_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QTimer>
#include "mypaper.h"
#include "myjudge.h"

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


signals:
    /*含义：开始答题信号*/
    void do_online_match();

    /*含义：回到主界面信号*/
    void do_MainWindow_show();

    /*含义：再来一次信号*/
    void do_OnlineAnser_show();

    /*含义：答对题目，告诉对方*/
    void do_anser_true();

public:
    void deal_show();   //恢复控件状态
    void deal_loop();   //延时函数
    void deal_button_result(int);  //响应答题
    void Result();  //答题结束，显示分数/题目数/总时长

    /*功能：线程向客户端传题*/
    void deal_recv_topix(QString,QString,QString,QString,QString,QString);

    /*功能：对方答对了题目*/
    void deal_your_true();

private slots:
    void on_Back_Button_clicked();
    void on_OneMore_Button_clicked();
    void on_match_Button_clicked();
    void on_A_Button_clicked();
    void on_B_Button_clicked();
    void on_C_Button_clicked();
    void on_D_Button_clicked();
    /*功能：处理一道题的时间到*/
    void OneTimerUpdate();

private:
    MyJudge *judge;
    int OneTime;
    QTimer *OneTimerId;

    int yourtime;
    int yourscore;
};

#endif // MYANSER_H
