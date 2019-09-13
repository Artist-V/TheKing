#include "logwidget.h"
#include "ui_logwidget.h"
#include <QMessageBox>


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
    ui->img_label->setFixedSize(565,130);
    movie->start();
    ui->img_label_2->setMovie(movie);
    ui->img_label_2->setFixedSize(565,130);

    //登录控件
    ui->name_lineEdit->setPlaceholderText(tr("用户名/ID号"));
    ui->pwd_lineEdit->setPlaceholderText(tr("请输入密码"));
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
    QRegExp re1("^[A-Za-z0-9_]{1,9}$");       ////由“数字、26个英文字母、下划线”组成的字符串
    QRegExp re2("^[A-Za-z0-9]{1,10}$");      ////由“数字、26个英文字母”组成的字符串
    ui->name_lineEdit->setValidator(new QRegExpValidator(re1,this));
    ui->pwd_lineEdit->setValidator(new QRegExpValidator(re2,this));

    //注册控件
    ui->name_lineEdit_2->setPlaceholderText(tr("长度[0,9]支持中文、英文、数字、下划线"));
    ui->pwd_lineEdit_2->setPlaceholderText(tr("长度[0,10]支持英文和数字"));
    ui->confirn_pwd_lineEdit->setPlaceholderText(tr("长度[0,10]支持英文和数字"));
    //ui->name_lineEdit_2->setEchoMode(QLineEdit::Password);
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
//    if(ui->name_lineEdit->text().isEmpty() || ui->pwd_lineEdit->text().isEmpty())
//    {
//        QMessageBox::warning(this,"警告","输入不可为空!",QMessageBox::Ok);
//    }
//    else
//    {
//        emit do_log_check(ui->name_lineEdit->text(),ui->pwd_lineEdit->text());
//    }
    deal_log_success();
}

void LogWidget::on_reg_Button_clicked()
{
    if(QString::compare(ui->pwd_lineEdit_2->text(),ui->confirn_pwd_lineEdit->text()) == 0)
    {
        emit do_reg_check(ui->name_lineEdit_2->text(),ui->pwd_lineEdit_2->text());
    }
    else
    {
        QMessageBox::warning(this,"警告","输入密码不一致，请重新输入",QMessageBox::Ok);
        ui->pwd_lineEdit_2->clear();
        ui->confirn_pwd_lineEdit->clear();
    }
}

void LogWidget::on_Exit_pushButton_clicked()
{
    this->close();
}

void LogWidget::on_reg_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    ui->name_lineEdit->clear();
    ui->pwd_lineEdit->clear();
}
void LogWidget::on_Exit_pushButton_2_clicked()
{
    deal_reg_success();
}

void LogWidget::deal_log_success()
{
    MainWindow *win = new MainWindow();
    win->show();
    this->hide();

    connect(win,SIGNAL(do_online_show()),this,SLOT(deal_online_show()));
    connect(win,SIGNAL(do_single_show()),this,SLOT(deal_single_show()));
    connect(win,SIGNAL(do_SendMessage(QString)),this,SLOT(deal_online_show()));

}

void LogWidget::deal_reg_success()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->name_lineEdit_2->clear();
    ui->pwd_lineEdit_2->clear();
    ui->confirn_pwd_lineEdit->clear();
}

void LogWidget::deal_message(QString message)
{
    QMessageBox::warning(this,"警告",message);
}


void LogWidget::deal_single_show()
{
    single = new MySingleAnser();
    single->show();

    connect(single,SIGNAL(do_single_start()),this,SLOT(deal_single_start()));
    connect(single,SIGNAL(do_MainWindow_show()),this,SLOT(deal_log_success()));
    connect(single,SIGNAL(do_SingleAnser_show()),this,SLOT(deal_single_show()));

}

void LogWidget::deal_online_show()
{
    online = new MyAnser();
    online->show();

    connect(online,SIGNAL(do_online_match()),this,SLOT(deal_online_match()));
    connect(online,SIGNAL(do_MainWindow_show()),this,SLOT(deal_log_success()));
    connect(online,SIGNAL(do_OnlineAnser_show()),this,SLOT(deal_online_show()));
    connect(online,SIGNAL(do_anser_true()),this,SLOT(deal_anser_true()));
}

void LogWidget::deal_SendMessage(QString s)
{
    emit do_SendMessage(s);
}

void LogWidget::deal_RecvMessage(QString name, QString time, QString message)
{
    emit do_RecvMessage(name,time,message);
}

void LogWidget::deal_single_start()
{
    emit do_request_single_topic();
}

void LogWidget::deal_online_match()
{
    emit do_online_match();
}

void LogWidget::deal_anser_true()
{
    emit do_anser_true();
}

void LogWidget::deal_topic_start(QString stem , QString a, QString b , QString c, QString d, QString True)
{
    single->deal_recv_topix(stem,a,b,c,d,True);
}

