#ifndef MYCONNECT_H
#define MYCONNECT_H
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <head.h>
#include "mysql.h"

class MyConnect : public QObject
{
    Q_OBJECT
public:
    explicit MyConnect(QObject *parent = 0);
    ~MyConnect();

signals:
    void do_Connect(nc_t nc);
    void do_String(QString str);
    void do_message(msg_t msg);

public slots:
    void deal_connect();
    void deal_disconnect();
    void deal_connect_error();
    void deal_read();
    void deal_CloseServer();
private:
    QTcpServer *Tserver;
    QTcpSocket *Tsocket;
    MySql *mysql;
public:
    void init_server();
};

#endif // MYCONNECT_H
