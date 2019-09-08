#ifndef MYTHREAD_H
#define MYTHREAD_H
#pragma execution_character_set("utf-8")
#include <QThread>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QDataStream>
#include <QMessageBox>
#include "head.h"

#define ServerPort 8080

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
    void do_topic(QString,QString,QString,QString,QString,QString);
    void do_recv_message(QString,QString,QString);

public slots:
    void deal_connect();        //连接成功
    void deal_disconnect();     //连接断开
    void deal_connect_error();  //连接异常
    void deal_tcp_read();       //处理TCP通信数据
    void deal_udp_read();       //处理UDP通信数据
    void deal_log_check(QString,QString);    //处理登录
    void deal_reg_check(QString,QString);    //处理注册
    void deal_request_single_topic();  //处理答题请求
    void deal_SendMessage(QString); //处理数据传输

public:
    void init_TCP();
    void init_UDP();
    void UDP_SendMessage(MessageType,QString message = "");
    void TCP_SendMessage(MessageType);

private:
    QString name;
    QString pwd;
    int type;
    QTcpSocket * Tsocket;
    QUdpSocket * Usocket;

};

#endif // MYTHREAD_H
