#ifndef LOGWIDGET_H
#define LOGWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMovie>
#include "mainwindow.h"
#include "mysingleanser.h"
#include "myanser.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
private:
    Ui::LogWidget *ui;

///////////////////////////////////////////////////
signals:
    void do_log(QString name,QString pwd);

private slots:
    void on_login_Button_clicked();
    void on_Exit_pushButton_clicked();
    void on_reg_pushButton_clicked();
    void on_Exit_pushButton_2_clicked();

//log+reg
    void deal_log_success();
    void deal_reg_success();
    void deal_message(QString);
//mainwindow
    void deal_single_show();
    void deal_online_show();


private:
    QMovie *movie;
};

#endif // LOGWIDGET_H
