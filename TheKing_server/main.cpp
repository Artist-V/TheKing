#include <QApplication>
#include "server.h"
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server win;
    win.show();

    return a.exec();
}
