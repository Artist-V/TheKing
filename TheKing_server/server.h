#ifndef SERVER_H
#define SERVER_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <head.h>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

signals:
    void do_OpenServer();
    void do_CloseServer();
private:
    Ui::Server *ui;

private slots:
    void on_OpenButton_clicked();
    void on_CloseButton_clicked();
    void deal_Connect(nc_t nc);
    void deal_String(QString str);
    void deal_Message(msg_t msg);
};

#endif // SERVER_H

//如果在Qt中要支持信号槽，需要这个类继承自QObject
