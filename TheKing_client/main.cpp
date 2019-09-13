#include <QApplication>
#include "mythread.h"
#include "logwidget.h"
#include "mysingleanser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogWidget win;
    win.show();

    MyThread *mythread = new MyThread;
    mythread->start();

    QObject::connect(&win,SIGNAL(do_log_check(QString,QString)),mythread,SLOT(deal_log_check(QString,QString)));
    QObject::connect(&win,SIGNAL(do_reg_check(QString,QString)),mythread,SLOT(deal_reg_check(QString,QString)));
    QObject::connect(&win,SIGNAL(do_request_single_topic()),mythread,SLOT(deal_request_single_topic()));
    QObject::connect(&win,SIGNAL(do_SendMessage(QString)),mythread,SLOT(deal_request_single_topic()));

    QObject::connect(mythread,SIGNAL(do_log_success()),&win,SLOT(deal_log_success()));
    QObject::connect(mythread,SIGNAL(do_reg_success()),&win,SLOT(deal_reg_success()));
    QObject::connect(mythread,SIGNAL(do_message(QString)),&win,SLOT(deal_message(QString)));
    QObject::connect(mythread,SIGNAL(do_topic(QString,QString,QString,QString,QString,QString)),\
                     &win,SLOT(deal_topic_start(QString,QString,QString,QString,QString,QString)));

    return a.exec();
}

/*
 * MainWindow：主菜单（单机答题，联机答题）
 * 一次一共10题
 *
 * MyPaper：草稿纸
 *
 * MySingleAnser:单机答题
 * *加载离线题库
 * *写入答题容器
 * *定时器：答题、切换题目的时间
 * **槽函数：开始答题，定时器启动，题目显示
 * **槽函数：点击答案，对比答案与正确答案，正确（绿色）/错误（红色），答对（加分）/答错（不加分）
 * **槽函数：定时器时间到，切换下一题
 *
 * MySingleAnser:单机答题
 * MyAnser:联机答题
 * LogWidget:登录+注册
 * MyThread:通信
 * *
 *
 *
 *
 *
 */


