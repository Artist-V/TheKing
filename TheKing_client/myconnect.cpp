#include "myconnect.h"

MyConnect::MyConnect(QObject *parent) : QObject(parent)
{
//通信
    Tsocket = new QTcpSocket(this);

    QString IP = " ";   //服务器IP
    qint16 TCPport = 9090;          //TCP端口
    //连接到服务器
    Tsocket->connectToHost(IP,TCPport);

    connect(Tsocket,SIGNAL(connected()),this,SLOT(deal_connect));
    connect(Tsocket,SIGNAL(disconnected()),this,SLOT(deal_disconnect));
    connect(Tsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(deal_connect_error()));
    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_read()));

//登录窗口
    mylog = new MyLog();
    mylog->show();

    connect(mylog,SIGNAL(do_log(QString,QString)),this,SLOT(deal_log(QString,QString)));
}

void MyConnect::deal_connect()
{

}

void MyConnect::deal_disconnect()
{

}

void MyConnect::deal_connect_error()
{

}

void MyConnect::deal_read()
{

}

void MyConnect::deal_log(QString name,QString pwd)
{
    this->name = name;
    this->pwd = pwd;
}

void MyConnect::deal_SendMessage(MessageType type)
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
