#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
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
    ui->img_label_2->setMovie(movie);
    ui->img_label_2->setFixedSize(565,130);

    //登录控件
    ui->name_lineEdit->setPlaceholderText(tr("用户名/ID号"));
    ui->pwd_lineEdit->setPlaceholderText(tr("请输入密码"));
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    QRegExp re1("^[A-Za-z0-9_]{1,9}$");       ////由数字、26个英文字母或者下划线组成的字符串
    QRegExp re2("^[A-Za-z0-9]{1,10}$");      ////由数字和26个英文字母组成的字符串
    ui->name_lineEdit->setValidator(new QRegExpValidator(re1,this));
    ui->pwd_lineEdit->setValidator(new QRegExpValidator(re2,this));
    //注册控件
    ui->name_lineEdit_2->setPlaceholderText(tr("长度[0,9]支持中文、英文、数字、下划线"));
    ui->pwd_lineEdit_2->setPlaceholderText(tr("长度[0,10]支持英文和数字"));
    ui->confirn_pwd_lineEdit->setPlaceholderText(tr("长度[0,10]支持英文和数字"));
    ui->name_lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->confirn_pwd_lineEdit->setEchoMode(QLineEdit::Password);
    ui->name_lineEdit_2->setValidator(new QRegExpValidator(re1,this));
    ui->pwd_lineEdit_2->setValidator(new QRegExpValidator(re2,this));
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::on_login_Button_clicked()
{

}

void LogWidget::on_Exit_pushButton_clicked()
{
    emit do_CloseServer();
    this->close();
}

void LogWidget::on_reg_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
