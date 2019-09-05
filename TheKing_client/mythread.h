#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma execution_character_set("utf-8")
#include <QThread>
#include <QTcpSocket>
#include "head.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();
signals:
    void do_ConnectClose();
public slots:
    void deal_connect();
    void deal_disconnect();
    void deal_connect_error();
    void deal_read();
    void deal_log(QString name,QString pwd);
    void deal_CloseServer();

public:
    void deal_SendMessage(MessageType type);
    void run();

private:
    QString name;
    QString pwd;
};

#endif // MYTHREAD_H
