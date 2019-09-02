#include "myanser.h"
#include "ui_myanser.h"

MyAnser::MyAnser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyAnser)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("头脑王者(对战模式)"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));
}

MyAnser::~MyAnser()
{
    delete ui;
}
