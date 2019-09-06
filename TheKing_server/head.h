#ifndef HEAD_H
#define HEAD_H
#include <QString>

enum MessageType
{
    LOG = 0x1010,    //登录
    REG,             //注册
    TOPIC,           //题目

    LOGSUC,
    LOGFAIL,
    REGSUC,
    REGFAIL
};

typedef struct message{
    QString name;
    QString pwd;
    int action;

}msg_t;

#endif // HEAD_H
