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

signals:
    void do_single_show();
    void do_online_show();

private slots:
    void on_single_Button_clicked();
    void on_online_Button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
