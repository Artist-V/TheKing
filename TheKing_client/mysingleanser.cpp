#include "mysingleanser.h"
#include "ui_mysingleanser.h"

MySingleAnser::MySingleAnser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MySingleAnser)
{
    ui->setupUi(this);
//ui
    this->setWindowTitle(tr("头脑王者(单机模式)"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));
//初始化
    topic.clear();
    qA.clear();
    qB.clear();
    qC.clear();
    qD.clear();
    qTrue.clear();
}

MySingleAnser::~MySingleAnser()
{
    delete ui;
}
