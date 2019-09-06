#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma execution_character_set("utf-8")
#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QMessageBox>
#include "head.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();
protected:
    void run();

signals:
    void do_log_success();
    void do_reg_success();
    void do_message(QString);

public slots:
    void deal_connect();        //连接成功
    void deal_disconnect();     //连接断开
    void deal_connect_error();  //连接异常
    void deal_read();           //处理通信数据
    void deal_log(QString name,QString pwd);    //处理登录

public:
    void deal_SendMessage(MessageType type);    //发送数据

private:
    QString name;
    QString pwd;
    QTcpSocket * Tsocket;
};

#endif // MYTHREAD_H
