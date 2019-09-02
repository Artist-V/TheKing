#ifndef MYLOG_H
#define MYLOG_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMovie>

namespace Ui {
class MyLog;
}

class MyLog : public QWidget
{
    Q_OBJECT

public:
    explicit MyLog(QWidget *parent = 0);
    ~MyLog();

signals:
    void do_log(QString name,QString pwd);
private slots:
    void on_login_Button_clicked();
    void on_Exit_pushButton_clicked();

private:
    Ui::MyLog *ui;
    QMovie *movie;
};

#endif // MYLOG_H
