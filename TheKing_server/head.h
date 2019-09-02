#ifndef HEAD_H
#define HEAD_H
#include <QString>

typedef struct connect{
    QString ip;
    quint16 port;
    QString str;
}nc_t;

typedef struct message{
    QString name;
    QString pwd;
    //QString str;
}msg_t;

enum MessageType
{
    Message,        //信息
    LOG             //登录

};

#endif // HEAD_H
