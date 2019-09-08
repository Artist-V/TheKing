#ifndef LOGWIDGET_H
#define LOGWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMovie>
#include "mainwindow.h"
#include "mysingleanser.h"
#include "myanser.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
private:
    Ui::LogWidget *ui;

signals://信号

    /*含义：检查登录*/
    void do_log_check(QString,QString);
    /*含义：检查注册*/
    void do_reg_check(QString,QString);
    /*含义：单机答题，请求服务器响应*/
    void do_request_single_topic();
    /*含义：处理数据*/
    void do_SendMessage(QString);
    /*含义：收到消息*/
    void do_RecvMessage(QString,QString,QString);
    /*含义：告诉对方我答对了*/
    void do_anser_true();
    /*含义：告诉线程请求匹配*/
    void do_online_match();

private slots://槽函数

    /*功能：发送do_log_check信号*/
    void on_login_Button_clicked();
    /*功能：发送do_reg_check信号*/
    void on_reg_Button_clicked();
    /*功能：关闭登录窗口*/
    void on_Exit_pushButton_clicked();
    /*功能：转到注册窗口*/
    void on_reg_pushButton_clicked();
    /*功能：转回登录窗口*/
    void on_Exit_pushButton_2_clicked();

//log+reg
    /*功能：登录成功，打开答题软件主界面*/
    void deal_log_success();
    /*功能：注册成功，转回登录界面*/
    void deal_reg_success();
    /* 功能：接收消息（一些错误信息，用消息框显示出来）
     * 参数：消息
     */
    void deal_message(QString);

//mainwindow
    /*功能：打开单机答题窗口*/
    void deal_single_show();
    /*功能：打开联机答题窗口*/
    void deal_online_show();
    /*功能：将输入发送的数据让线程处理*/
    void deal_SendMessage(QString);
    /*功能：收到UDP消息*/
    void deal_RecvMessage(QString, QString, QString);


//mysingleanser
    /*功能：单机答题开始，请求服务器发送题目*/
    void deal_single_start();

    //void deal_MainWindow_show();  同 deal_log_success();
    //void deal_SingleAnser_show(); 同 deal_single_show();
//myanser
    /*功能：处理联机匹配*/
    void deal_online_match();
    void deal_anser_true();

//
    /*功能：传题*/
    void deal_topic_start(QString,QString,QString,QString,QString,QString);

private:
    QMovie *movie;
    MySingleAnser * single;
    MyAnser * online;

};

#endif // LOGWIDGET_H
