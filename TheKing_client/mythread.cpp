#include "mythread.h"
#include <QDebug>
#include <QDataStream>
MyThread::MyThread(QObject *parent) : QThread(parent)
{
//通信
    Tsocket = new QTcpSocket(this);

    QString IP = "127.0.0.1";   //服务器IP
    qint16 TCPport = 9090;          //TCP端口
    //连接到服务器
    Tsocket->connectToHost(IP,TCPport);

    connect(Tsocket,SIGNAL(connected()),this,SLOT(deal_connect()));
    connect(Tsocket,SIGNAL(disconnected()),this,SLOT(deal_disconnect()));
    connect(Tsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(deal_connect_error()));
    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_read()));

}
MyThread::~MyThread()
{
    delete Tsocket;
}
void MyThread::deal_CloseServer()
{
    Tsocket->close();
}

void MyThread::deal_connect()
{
    qDebug() << "连接服务器成功";
}

void MyThread::deal_disconnect()
{
    emit do_ConnectClose();
    qDebug() << "与服务器连接断开";
}

void MyThread::deal_connect_error()
{
    emit do_ConnectClose();
    qDebug() << "与服务器连接异常";
}

void MyThread::deal_read()
{

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
