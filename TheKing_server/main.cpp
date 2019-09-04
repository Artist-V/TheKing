#include <QApplication>
#include "server.h"
#include "mythread.h"
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server win;
    win.show();

    MyThread *mythread = new MyThread;

    QObject::connect(mythread,SIGNAL(do_Connect(nc_t)),&win,SLOT(deal_Connect(nc_t)));   //处理连接
    QObject::connect(mythread,SIGNAL(do_String(QString)),&win,SLOT(deal_String(QString)));
    QObject::connect(mythread,SIGNAL(do_message(msg_t)),&win,SLOT(deal_Message(msg_t)));

    QObject::connect(&win,SIGNAL(do_OpenServer()),mythread,SLOT(init_server()));
    QObject::connect(&win,SIGNAL(do_CloseServer()),mythread,SLOT(deal_CloseServer()));

    return a.exec();
}
