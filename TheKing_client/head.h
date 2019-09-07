#ifndef HEAD_H
#define HEAD_H
#include <QString>

/*通信状态码*/
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

/*通信消息包*/
typedef struct message{
    QString name;
    QString pwd;
    MessageType action;

}msg_t;

#endif // HEAD_H
