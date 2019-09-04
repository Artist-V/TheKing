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
    void do_Connect(nc_t nc);
    void do_String(QString str);
    void do_message(msg_t msg);

public slots:
    void init_server();
    void deal_connect();
    void deal_disconnect();
    void deal_connect_error();
    void deal_read();
    void deal_CloseServer();

private:
    QTcpServer *Tserver;
    QTcpSocket *Tsocket;
    MySql *mysql;

};

#endif // MYTHREAD_H

//void stop();
//volatile bool stopped;  //在任何时候都保持最新的值，避免在多个线程中访问出错
