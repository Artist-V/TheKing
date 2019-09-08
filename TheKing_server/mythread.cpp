#include "mythread.h"
#include <QDebug>
#include <QDataStream>
#include <QTime>

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
MyThread::~MyThread()
{
    delete Tserver;
    delete Tsocket;
}
void MyThread::init_TCP()
{
    Tsocket = new QTcpSocket();
    Tserver = new QTcpServer();

    quint16 port = 9090;
    Tserver->listen(QHostAddress::Any,port);

    connect(Tserver,SIGNAL(newConnection()),this,SLOT(deal_connect()));
}

void MyThread::init_UDP()
{
    Usocket = new QUdpSocket();

    Usocket->bind(QHostAddress::LocalHost,8080);

    connect(Usocket,SIGNAL(readyRead()),this,SLOT(deal_udp_read()));

}

QString MyThread::Generate_Random()
{

    QTime time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);
    return QString::number(qrand() % 9);    //产生9以内的随机数
}

void MyThread::run()
{
    room = 1;
    WaitList.clear();
    roomList.clear();

    mysql = new MySql();
    connect(mysql,SIGNAL(Send_topic(QString,QString,QString,QString,QString,int,int)),\
            this,SLOT(Recv_topic(QString,QString,QString,QString,QString,int,int)));

    init_TCP();
    init_UDP();

    this->exec();
}

//处理客户端连接
void MyThread::deal_connect()
{
    Tsocket = Tserver->nextPendingConnection();

    QString ip = Tsocket->peerAddress().toString();
    int port = Tsocket->peerPort();

    emit send_ipandport(ip,port);

    connect(Tsocket,SIGNAL(readyRead()),this,SLOT(deal_tcp_read()));
}


//通信数据处理
void MyThread::deal_tcp_read()
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
                //生成随机ID
                msg.id = Generate_Random();
                qDebug() << msg.id;
                //用户名/密码插入用户表
                mysql->insert_uid(msg.id,msg.name,msg.pwd);
                //注册成功
                emit do_message(msg);
                SendToClient(REGSUC,msg.name);
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

void MyThread:: deal_udp_read()
{
    QByteArray data;
    QDataStream in(&data,QIODevice::ReadOnly);

    data = Usocket->readAll();

    int type;
    in >> type;

    umsg_t umsg;
    memset(&umsg,0,sizeof(umsg_t));
    umsg.ip = Usocket->peerAddress().toString();
    umsg.port = Usocket->peerPort();

    switch(type)
    {
    //消息（广播）
    case MESSAGE:
        in >> umsg.name >> umsg.message;
        emit do_udp_message(umsg);

        break;

    //请求答题
    case REQUEST:
        in >> umsg.name >> umsg.topic;
        emit do_udp_message(umsg);

        //处理请求
        deal_request(umsg.topic,umsg);

        break;
    }

}

void MyThread::Recv_topic(QString stem, QString a, QString b, QString c, QString d, int True, int room)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out << stem << a << b << c << d << True;
//    QHostAddress addr1 = WaitList.at(2 * (room - 1)).ip;
//    QHostAddress addr2 = WaitList.at(2 * (room - 1) + 1).ip;
    Usocket->writeDatagram(data,/*addr1*/WaitList.at(2 * (room - 1)).ip,WaitList.at(2 * (room - 1)).port);
    Usocket->writeDatagram(data,/*addr2*/WaitList.at(2 * (room - 1) + 1).ip,WaitList.at(2 * (room - 1) + 1).port);
}

//向客户端发送数据
void MyThread::SendToClient(int type,QString name)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out << type ;

    switch(type)
    {
    case LOGSUC:
            out << name;
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

void MyThread::deal_request(int type,umsg_t umsg)
{
    switch(type)
    {
//单机答题
    case SINGLE:

        //从数据库中抽取20题
        mysql->Generate_Random_single(SINGLE_NUM);

        //信号
        break;


//联机答题
    case ONLINE:
        //加入链表
        usr_t user;
        memset(&user,0,sizeof(usr_t));

        user.ip = umsg.ip;
        user.port = umsg.port;
        user.name = umsg.name;

        WaitList.push_back(user);

        //等待用户加入
        if(WaitList.size() >= 2)
        {
            roomList.push_back(room);
            room++;
            //从数据库中抽取5题
            mysql->Generate_Random(ONLINE_NUM,roomList.at(room));
        }


        break;
    }
}
