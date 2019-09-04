#include "mythread.h"
#include <QDebug>
#include <QDataStream>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

    //初始化
    mysql = new MySql(this);

    Tserver = new QTcpServer(this);
    Tsocket = new QTcpSocket(this);
}
MyThread::~MyThread()
{
    delete Tserver;
    //断连
    delete Tsocket;
}

void MyThread::run()
{

}
void MyThread::deal_CloseServer()
{
    Tserver->close();
    Tsocket->close();
}

//等server窗口点击“开启服务器”才初始化
void MyThread::init_server()
{
    quint16 port = 9090;
    Tserver->listen(QHostAddress::Any,port);
    emit do_String(QString("初始化Tserver,端口号9090"));
    connect(Tserver,SIGNAL(newConnection()),this,SLOT(deal_connect()));
}

void MyThread::deal_connect()
{
    Tsocket = Tserver->nextPendingConnection();
    nc_t nc;
    nc.ip = Tsocket->peerAddress().toString();
    nc.port = Tsocket->peerPort();
    nc.str = "新客户端连接";

    //server->setTextBrowser(ip,port,"新客户端连接");
    emit do_Connect(nc);

    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_read()));
    connect(Tsocket,SIGNAL(disconnected()),this,SLOT(deal_disconnect()));
    connect(Tsocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(deal_connect_error()));
}

void MyThread::deal_disconnect()
{
    nc_t nc;
    nc.ip = Tsocket->peerAddress().toString();
    nc.port = Tsocket->peerPort();
    nc.str = "客户端关闭连接";

    //server->setTextBrowser(ip,port,"客户端关闭连接");
    emit do_Connect(nc);
}

void MyThread::deal_connect_error()
{
    emit do_String(QString("服务器异常！"));
}

void MyThread::deal_read()
{
    QByteArray data;
    Tsocket->readAll();
    QDataStream in(&data,QIODevice::ReadOnly);

    int type;
    in >> type;

    //QString name,pwd;
    nc_t nc;
    nc.ip = Tsocket->peerAddress().toString();
    nc.port = Tsocket->peerPort();

    msg_t msg;
    switch(type)
    {
        case LOG:
            qDebug()<<"read : LOG";

            in >> msg.name >> msg.pwd ;

            //检查用户名和密码
            if(mysql->check_uid(msg.name,msg.pwd))
            {
                emit do_message(msg);
            }
            else
            {
                emit do_String(QString("IP[%1] port[%2]用户登陆失败").arg(nc.ip).arg(QString::number(nc.port)));
            }
            break;
    }
}


//stopped = false;

//void MyThread::stop()
//{
//    stopped = true;
//}
