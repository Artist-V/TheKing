#include "mypaper.h"
#include "ui_mypaper.h"

MyPaper::MyPaper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyPaper)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("草稿纸"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));
}

MyPaper::~MyPaper()
{
    delete ui;
}
