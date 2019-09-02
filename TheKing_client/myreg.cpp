#include "myreg.h"
#include "ui_myreg.h"

MyReg::MyReg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyReg)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("用户注册"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));

//ui
    //动图
    movie = new QMovie(":/pic/pic1.gif");
    ui->img_label->setMovie(movie);
    ui->img_label->setFixedSize(380,130);
    movie->start();
    //控件
    ui->name_lineEdit->setPlaceholderText(tr("长度[0,9]支持中文、英文、数字、下划线"));
    ui->pwd_lineEdit->setPlaceholderText(tr("长度[0,10]支持英文和数字"));
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    QRegExp re1("^[A-Za-z0-9_]{1,9}$");       ////由数字、26个英文字母或者下划线组成的字符串
    QRegExp re2("^[A-Za-z0-9]{1,10}$");      ////由数字和26个英文字母组成的字符串
    ui->name_lineEdit->setValidator(new QRegExpValidator(re1,this));
    ui->pwd_lineEdit->setValidator(new QRegExpValidator(re2,this));
}

MyReg::~MyReg()
{
    delete ui;
}
