#ifndef MYSQL_H
#define MYSQL_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class MySql : public QObject
{
    Q_OBJECT
public:
    explicit MySql(QObject *parent = 0);
    ~MySql();
signals:
    void Send_topic(QString,QString,QString,QString,QString,int,int);
    void Send_topic_single(QString,QString,QString,QString,QString,int);
public slots:

private:
    QSqlDatabase db;
public:
    void connect_database();//连接数据库
    void create_table();//创建表
    void close_mysql();// 关闭数据库
    bool check_uid(QString uid, QString upwd);//登录：检查用户账号密码是否有效
    void insert_uid(QString uid, QString uname,QString upwd);//插入新用户
    bool check_insert(QString uid);//注册：检查uid是否存在
    void update(QString type,QString uid,QString something);//修改(按type来修改)

    /*入参：单机 20; 联机 5*/
    void Generate_Random_single(int);
    void Generate_Random(int,int);
};

#endif // MYSQL_H
