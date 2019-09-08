#include "server.h"
#include "ui_server.h"
#include <QDateTime>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
//ui
    ui->setupUi(this);
    this->setWindowTitle(tr("TheKing Server :9090"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));

//mythread
    mythread = new MyThread();

}

Server::~Server()
{
    delete ui;
}

//开启服务器
void Server::on_OpenButton_clicked()
{
    ui->OpenButton->setEnabled(false);
    ui->CloseButton->setEnabled(true);

    //开启服务
    ui->textBrowser->append(QString("----------开启服务器----------"));
    //if(!mythread->isRunning())
    //{
        mythread->start();
        connect(mythread,SIGNAL(send_ipandport(QString,int)),this,SLOT(deal_recv_ipandport(QString,int)));
    //}
}
//关闭服务器
void Server::on_CloseButton_clicked()
{
    ui->CloseButton->setEnabled(false);
    ui->OpenButton->setEnabled(true);

    ui->textBrowser->append(QString("----------关闭服务器----------"));

}

void Server::deal_recv_ipandport(QString ip, int port)
{
    ui->textBrowser->append(QString("[new] client connect IP[%1],PORT[%2] ").arg(ip).arg(QString::number(port)));
}

void Server::deal_message(QString ip,int port,QString name,QString message)
{
    ui->textBrowser->append(QString("ip[%1],port[%2] client[%3]:[%4]").\
                            arg(ip).arg(QString::number(port)).arg(name).arg(message));
}

void Server::deal_request(QString ip,int port,QString name,int topic)
{
    ui->textBrowser->append(QString("ip[%1],port[%2] client[%3] request %4 Anser Sheet").\
                            arg(ip).arg(QString::number(port)).arg(name).arg(QString::number(topic)));
}

