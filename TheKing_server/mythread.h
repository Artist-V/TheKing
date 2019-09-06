#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma execution_character_set("utf-8")
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <head.h>
#include "mysql.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();
protected:
    void run();

signals:
    void do_String(QString);
    void do_message(msg_t);
    void send_ipandport(QString,int); //连接服务器的客户端IP/PORT

public slots:
    void deal_connect(); //处理连接
    void deal_read();    //处理接收数据

public:
    void SendToClient(MessageType type); //向客户端发送消息

private:
    QTcpServer *Tserver;
    QTcpSocket *Tsocket;
    MySql *mysql;

};

#endif // MYTHREAD_H

