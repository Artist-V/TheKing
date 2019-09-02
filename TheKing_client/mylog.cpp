#include "mylog.h"
#include "ui_mylog.h"

MyLog::MyLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyLog)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("用户登录"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));

//ui
    //动图
    movie = new QMovie(":/pic/pic1.gif");
    ui->img_label->setMovie(movie);
    ui->img_label->setFixedSize(380,130);
    movie->start();
    //控件
    ui->name_lineEdit->setPlaceholderText(tr("请输入用户名/ID号"));
    ui->pwd_lineEdit->setPlaceholderText(tr("请输入密码"));
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    QRegExp re1("^[A-Za-z0-9_]{1,9}$");       ////由数字、26个英文字母或者下划线组成的字符串
    QRegExp re2("^[A-Za-z0-9]{1,10}$");      ////由数字和26个英文字母组成的字符串
    ui->name_lineEdit->setValidator(new QRegExpValidator(re1,this));
    ui->pwd_lineEdit->setValidator(new QRegExpValidator(re2,this));
}

MyLog::~MyLog()
{
    delete ui;
}

void MyLog::on_login_Button_clicked()
{
    emit do_log(ui->name_lineEdit->text(),ui->pwd_lineEdit->text());
}

void MyLog::on_Exit_pushButton_clicked()
{

}
