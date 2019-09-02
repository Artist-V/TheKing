#ifndef MYCONNECT_H
#define MYCONNECT_H
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QTcpSocket>
#include "mylog.h"
#include "head.h"

class MyConnect : public QObject
{
    Q_OBJECT
public:
    explicit MyConnect(QObject *parent = 0);

signals:

public slots:
    void deal_connect();
    void deal_disconnect();
    void deal_connect_error();
    void deal_read();
    void deal_log(QString name,QString pwd);
public:
    void deal_SendMessage(MessageType type);
private:
    QTcpSocket *Tsocket;
    MyLog *mylog;
    QString name;
    QString pwd;
};

#endif // MYCONNECT_H
