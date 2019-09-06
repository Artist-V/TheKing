#include "mythread.h"
#include <QDebug>
#include <QDataStream>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
MyThread::~MyThread()
{
    delete Tserver;
    delete Tsocket;
}

void MyThread::run()
{
    mysql = new MySql();
    Tsocket = new QTcpSocket();
    Tserver = new QTcpServer();

    quint16 port = 9090;
    Tserver->listen(QHostAddress::Any,port);

    connect(Tserver,SIGNAL(newConnection()),this,SLOT(deal_connect()));

    this->exec();
}

//处理客户端连接
void MyThread::deal_connect()
{
    Tsocket = Tserver->nextPendingConnection();

    QString ip = Tsocket->peerAddress().toString();
    int port = Tsocket->peerPort();

    emit send_ipandport(ip,port);

    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_read()));
}


//通信数据处理
void MyThread::deal_read()
{
    QByteArray data;
    QDataStream in(&data,QIODevice::ReadOnly);

    data = Tsocket->readAll();

    int type;
    in >> type;

    QString ip = Tsocket->peerAddress().toString();
    int port = Tsocket->peerPort();

    msg_t msg;
    memset(&msg,0,sizeof(msg_t));

    switch(type)
    {
//登录
        case LOG:
            qDebug()<<"read : LOG";
            msg.action = LOG;
            in >> msg.name >> msg.pwd ;

    //检查用户名和密码
            if(mysql->check_uid(msg.name,msg.pwd))
            {
                //登录成功
                emit do_message(msg);
                SendToClient(LOGSUC);
            }
            else
            {
                //登录失败
                emit do_String(QString("IP[%1] port[%2] 用户登陆失败").arg(ip).arg(QString::number(port)));
                SendToClient(LOGFAIL);
            }
            break;
//注册
    case REG:
            qDebug()<<"read : REG";
            msg.action = REG;
            in >> msg.name >> msg.pwd ;

    //检查用户名是否存在
            if(mysql->check_insert(msg.name))
            {
                //注册成功
                emit do_message(msg);
                SendToClient(REGSUC);
            }
            else
            {
                //注册失败
                emit do_String(QString("IP[%1] port[%2] 用户注册失败").arg(ip).arg(QString::number(port)));
                SendToClient(REGFAIL);
            }
            break;
    }
}

//向客户端发送数据
void MyThread::SendToClient(MessageType type)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out << type ;

    switch(type)
    {
    case LOGSUC:
            qDebug() << "send : LOGSUC";
            break;
    case LOGFAIL:
            qDebug() << "send : LOGFAIL";
            break;
    case REGSUC:
            qDebug() << "send : REGSUC";
            break;
    case REGFAIL:
            qDebug() << "send : REGFAIL";
            break;
    }
    Tsocket->write(data);
}
