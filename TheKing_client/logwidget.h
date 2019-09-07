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

private slots://槽函数

    /*功能：发送do_log信号*/
    void on_login_Button_clicked();
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


    void on_reg_Button_clicked();

private:
    QMovie *movie;
};

#endif // LOGWIDGET_H
