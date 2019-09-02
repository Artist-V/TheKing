#include <QApplication>
//#include "myconnect.h"
#include "server.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MyConnect conn;
    Server win;
    win.show();

    return a.exec();
}
