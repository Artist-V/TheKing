#ifndef SERVER_H
#define SERVER_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "head.h"
#include "mythread.h"

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
private:
    Ui::Server *ui;

signals:

private slots:
    void on_OpenButton_clicked();
    void on_CloseButton_clicked();
    void deal_recv_ipandport(QString,int);  //连接的客户端IP/PORT
    void deal_message(QString,int,QString,QString);
    void deal_request(QString,int,QString,int);

private:
    MyThread *mythread;


};

#endif // SERVER_H

//如果在Qt中要支持信号槽，需要这个类继承自QObject
