#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
MyThread::~MyThread()
{
    delete Tsocket;
}

void MyThread::run()
{
    Tsocket = new QTcpSocket();

    QString IP = "127.0.0.1";   //服务器IP
    qint16 TCPport = 9090;      //TCP端口
    Tsocket->connectToHost(IP,TCPport);

    connect(Tsocket,SIGNAL(connected()),this,SLOT(deal_connect()));
    connect(Tsocket,SIGNAL(disconnected()),this,SLOT(deal_disconnect()));
    connect(Tsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(deal_connect_error()),Qt::DirectConnection);
    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_read()));

    this->exec();
}


//连接成功
void MyThread::deal_connect()
{
    qDebug() << "连接服务器成功";
}

//连接断开
void MyThread::deal_disconnect()
{
    emit do_message("与服务器连接断开");
}

//连接异常
void MyThread::deal_connect_error()
{
    emit do_message("与服务器连接异常");
}

//数据通信
void MyThread::deal_read()
{
    QByteArray data;
    QDataStream in(&data,QIODevice::ReadOnly);

    data = Tsocket->readAll();

    int type;
    in >> type;

    switch(type)
    {
//登陆成功
    case LOGSUC:
        emit do_log_success();
        break;
//登陆失败
    case LOGFAIL:
        emit do_message("登录失败!请检查用户名和密码!");
        break;
//注册成功
    case REGSUC:
        emit do_reg_success();
        break;
//注册失败
    case REGFAIL:
        emit do_message("注册失败!用户名已被使用!");
        break;
    }
}

void MyThread::deal_log(QString name,QString pwd)
{
    this->name = name;
    this->pwd = pwd;
}

void MyThread::deal_SendMessage(MessageType type)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << type ;
    switch (type)
    {
    case LOG:
        out << name << pwd;
        qDebug()<<"check LOG";
        break;
    }
    Tsocket->write(data);
}
