#ifndef HEAD_H
#define HEAD_H
#include <QString>
#include <QHostAddress>

/*通信状态码*/
enum MessageType
{
    LOG = 0x1010,    //登录
    REG,             //注册
    REQUEST,         //请求题目
    TOPIC,           //发送题目
    MESSAGE,         //信息

    LOGSUC,
    LOGFAIL,
    REGSUC,
    REGFAIL,

    SINGLE, //单机
    ONLINE, //连网
};

/*通信消息包*/
typedef struct message{
    QString name;
    QString pwd;
    MessageType action;

}msg_t;

/*UDP通信消息包*/
typedef struct umessage{
    QHostAddress ip;
    quint16 port;
    QString name;
    QString message;
    int topic;

}umsg_t;

#endif // HEAD_H
