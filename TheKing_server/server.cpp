﻿#include "server.h"
#include "ui_server.h"
#include <QDateTime>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    //UI
    ui->setupUi(this);
    this->setWindowTitle(tr("TheKing Server :9090"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));

    //初始化
    myconn = new MyConnect();
    connect(myconn,SIGNAL(do_Connect(nc_t)),this,SLOT(deal_Connect(nc_t)));
    connect(myconn,SIGNAL(do_String(QString)),this,SLOT(deal_String(QString)));
    connect(myconn,SIGNAL(do_message(QDataStream)),this,SLOT(deal_Message(QDataStream)));

}

Server::~Server()
{
    delete ui;
}

void Server::init_sql()
{

}

//开启服务器
void Server::on_OpenButton_clicked()
{
    //开启服务
    ui->textBrowser->append(QString("----------开启服务器----------"));
    myconn->init_server();

}
//关闭服务器
void Server::on_CloseButton_clicked()
{
    ui->textBrowser->append(QString("----------关闭服务器----------"));
    myconn->deal_CloseServer();
}

void Server::deal_String(QString str)
{
    QString s = QString("[new] %1").arg(str);
    ui->textBrowser->append(s);
}

void Server::deal_Message(msg_t msg)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textBrowser->append(time);
    ui->textBrowser->append(QString("ID[%1] PWD[%2] 用户登录成功").arg(msg.name).arg(msg.pwd));
}

void Server::deal_Connect(nc_t nc)
{
    QString ip = nc.ip;
    qint16 port = nc.port;
    QString str = nc.str;
    QString s = QString("IP[%1] port[%2] : %3").arg(ip).arg(QString::number(port)).arg(str);
    ui->textBrowser->append(s);
}