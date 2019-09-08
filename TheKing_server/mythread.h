#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma execution_character_set("utf-8")
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <head.h>
#include "mysql.h"

#define SINGLE_NUM 20
#define ONLINE_NUM 5

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
    void do_udp_message(umsg_t/*QString,int,QString,QString*/);
    /*void do_request(QString,int,QString,int);*/

public slots:
    void deal_connect(); //处理连接
    void deal_tcp_read();   //处理接收TCP数据
    void deal_udp_read();   //处理接收UDP数据
    void Recv_topic(QString,QString,QString,QString,QString,int,int);

public:
    void init_TCP();
    void init_UDP();
    QString Generate_Random();
    void SendToClient(int,QString name = ""); //向客户端发送消息
    void deal_request(int,umsg_t);


private:
    QTcpServer *Tserver;
    QTcpSocket *Tsocket;
    MySql *mysql;
    QUdpSocket *Usocket;

    QVector<usr_t> WaitList;
    QVector<int> roomList;
    int room;

};

#endif // MYTHREAD_H

