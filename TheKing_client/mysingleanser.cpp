#include "mysingleanser.h"
#include "ui_mysingleanser.h"

MySingleAnser::MySingleAnser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MySingleAnser)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("头脑王者(单机模式)"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));
}

MySingleAnser::~MySingleAnser()
{
    delete ui;
}
