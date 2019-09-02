#include "mysql.h"
#include <QDebug>

MySql::MySql(QObject *parent) : QObject(parent)
{

}

MySql::~MySql()
{
    db.close();
}

void MySql::connect_database()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("theking");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        qDebug()<<"连接数据库失败"<<db.lastError().text();
        return ;
    }
}

void MySql::create_table()
{
    QSqlQuery query(db);
    query.exec("create table if not exists user("
               "uid int(11) PRIMARY KEY NOT NULL , "
               "upwd varchar(15) NOT NULL, "
               "uname varchar(15) NOT NULL)");
    //若数据库中没有用户表则创建用户表
    //数据库中一定会有题库的题目，所以不需要创建题库表
}

void MySql::close_mysql()
{
    db.close();
}

bool MySql::check_uid(QString uid, QString upwd)
{
    QSqlQuery query(db);
    QString sql = QString("select * from user where uid = '%1' and upwd = '%2'").arg(uid).arg(upwd);
    query.exec(sql);
    query.next();
    if((query.at()) == 0)  //query指向的记录在结果集中的编号
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MySql::insert_uid(QString uid, QString uname, QString upwd)
{
    QSqlQuery query(db);
    QString sql = QString("insert into user values('%1','%2','%3')").arg(uid).arg(uname).arg(upwd);
    query.exec(sql);
}

bool MySql::check_insert(QString uid)
{
    QSqlQuery query(db);
    QString sql = QString("select * from user where uid = '%1'").arg(uid);
    query.exec(sql);
    query.next();
    if((query.at()) == 0)  //query指向的记录在结果集中的编号
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MySql::update(QString type,QString uid, QString something)
{
    QSqlQuery query(db);
    QString sql;
    if(QString::compare(type,"name") == 0)
    {
        sql = QString("update user set uname = '%1' where uid = '%2'").arg(something).arg(uid);
    }
    else if(QString::compare(type,"pwd") == 0)
    {
        sql = QString("update user set upwd='%1' where uid = '%2'").arg(something).arg(uid);
    }
    query.exec(sql);
}



















