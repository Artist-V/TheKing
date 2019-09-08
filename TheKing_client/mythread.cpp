#include "mythread.h"
#include <QDebug>
#include <QHostAddress>
#include <QDateTime>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
MyThread::~MyThread()
{
    delete Tsocket;
}
void MyThread::init_TCP()
{
    Tsocket = new QTcpSocket();

    qint16 TCPport = 9090;      //TCP端口

    Tsocket->connectToHost(QHostAddress::LocalHost,TCPport);

    connect(Tsocket,SIGNAL(connected()),this,SLOT(deal_connect()));
    connect(Tsocket,SIGNAL(disconnected()),this,SLOT(deal_disconnect()));
    connect(Tsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(deal_connect_error()),Qt::DirectConnection);
    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_tcp_read()));

}

void MyThread::init_UDP()
{
    Usocket = new QUdpSocket();

    Usocket->bind(QHostAddress::LocalHost);//port不选择，让系统挑选一个空闲的端口

    connect(Usocket,SIGNAL(readyRead()),this,SLOT(deal_udp_read()));

}

void MyThread::run()
{
    init_TCP();
    init_UDP();

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

void MyThread::deal_udp_read()
{
    QByteArray data;
    QDataStream in(&data,QIODevice::ReadOnly);

    data = Usocket->readAll();

    int type;
    in >> type;


    QString stem,qA,qB,qC,qD,qTrue;
    QString message;
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    switch(type)
    {
//题目
    case TOPIC:
        in >> stem >> qA >> qB >> qC >> qD >> qTrue;
        emit do_topic(stem,qA,qB,qC,qD,qTrue);
        break;

    case MESSAGE:
        in >> name >> message;
        emit do_recv_message(name,time,message);
        break;
    }
}

void MyThread::UDP_SendMessage(MessageType type,QString message)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    switch(type)
    {
//    case MESSAGE:
//    //广场信息
//        out << MESSAGE << name << message;
//        break;

    //
    case REQUEST:
        out << REQUEST << name << this->type;
        break;
    }
    Usocket->writeDatagram(data,QHostAddress::LocalHost,ServerPort);
}

//数据通信
void MyThread::deal_tcp_read()
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
        in >> this->name; //当前用户
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
void MyThread::TCP_SendMessage(MessageType type)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out << type;

    switch(type)
    {
    case REG:
        out << REG << name << pwd;
        break;

    case LOG:
        out << LOG << name << pwd;
        break;
    }

    Tsocket->write(data);
}

void MyThread::deal_reg_check(QString name, QString pwd)
{
    this->name = name;
    this->pwd = pwd;
    TCP_SendMessage(REG);
}

void MyThread::deal_log_check(QString name,QString pwd)
{
    this->name = name;
    this->pwd = pwd;
    TCP_SendMessage(LOG);
}

void MyThread::deal_request_single_topic()
{
    this->type = SINGLE;
    UDP_SendMessage(REQUEST);
}

void MyThread::deal_SendMessage(QString s)
{
//    UDP_SendMessage(MESSAGE,s);
    QByteArray data = s.toLatin1();
    Usocket->writeDatagram(data,QHostAddress::Broadcast,8081);
}
