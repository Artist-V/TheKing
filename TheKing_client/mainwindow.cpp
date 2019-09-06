#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("头脑王者"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_single_Button_clicked()
{
    emit do_single_show();
}

void MainWindow::on_online_Button_clicked()
{
    emit do_online_show();
}
