#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>


//头脑王者答题软件主界面

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

signals://信号

    /*含义：开启单机答题窗口*/
    void do_single_show();

    /*含义：开启联机答题窗口*/
    void do_online_show();

private slots: //槽函数

    /*功能：发送do_single_show信号*/
    void on_single_Button_clicked();

    /*功能：发送do_online_show信号*/
    void on_online_Button_clicked();


};

#endif // MAINWINDOW_H
