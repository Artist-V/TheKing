#ifndef LOGWIDGET_H
#define LOGWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMovie>

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
    void do_CloseServer();

private slots:
    void on_login_Button_clicked();
    void on_Exit_pushButton_clicked();

private:
    QMovie *movie;
};

#endif // LOGWIDGET_H
