#include "myanser.h"
#include "ui_myanser.h"
#include <QDebug>


MyAnser::MyAnser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyAnser)
{
    ui->setupUi(this);
//ui
    this->setWindowTitle(tr("头脑王者(对战模式)"));
    this->setWindowIcon(QPixmap(":/icon/熊猫.png"));

//判决
    judge = new MyJudge();

//每题的计时器
    OneTime = 30;
    OneTimerId = new QTimer();
    connect(OneTimerId,SIGNAL(timeout()),this,SLOT(OneTimerUpdate()));
//
    yourscore = 0;
    yourtime = 0;


////测试
//    judge->test();
//    deal_show();
//    ui->stackedWidget->setCurrentIndex(2);
//    judge->OpenTimer();
//    OneTimerId->start(1000);
}


MyAnser::~MyAnser()
{
    delete ui;
}

void MyAnser::OneTimerUpdate()
{
    if(OneTime)
    {
        OneTime--;
        ui->time_label->setText(QString::number(OneTime));
    }
    else
    {
        //一题的时间到，换题
        deal_show();

        //重置计时器
        OneTime = 30;
    }
}

void MyAnser::deal_show()
{
    //按钮样式恢复
    ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(225,225,225)}");
    ui->A_Button->update();
    ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(225,225,225)}");
    ui->B_Button->update();
    ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(225,225,225)}");
    ui->C_Button->update();
    ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(225,225,225)}");
    ui->D_Button->update();

    //状态恢复
    ui->A_Button->setEnabled(true);
    ui->B_Button->setEnabled(true);
    ui->C_Button->setEnabled(true);
    ui->D_Button->setEnabled(true);

    //计入题目数量
    judge->SetTopicNum();

    if(!judge->Check_CurrentIndex())
    {

        ui->topic_textEdit->setText(judge->TopicAt());
        ui->A_Button->setText(judge->qaAt());
        ui->B_Button->setText(judge->qbAt());
        ui->C_Button->setText(judge->qcAt());
        ui->D_Button->setText(judge->qdAt());

        if(!judge->Check_CurrentIndex())
        {
            judge->SetCurrentIndex();
        }
    }
}

void MyAnser::deal_loop()
{
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();
}

void MyAnser::deal_button_result(int index)
{
    if(judge->Check_Anser(index))
    {
        emit do_anser_true();
    }
    ui->mscore_label->setText(QString::number(judge->GetScore()));
    ui->mscore_label->update();

    qDebug() << "judge->GetTrueIndex() = " << judge->GetTrueIndex();

    //显示正确答案
    switch (judge->GetTrueIndex())
    {
    case 1:
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->A_Button->update();
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->B_Button->update();
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->C_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 2:
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->B_Button->update();
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->A_Button->update();
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->C_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 3:
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->C_Button->update();
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->A_Button->update();
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->B_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 4:
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->D_Button->update();
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->A_Button->update();
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->B_Button->update();
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->C_Button->update();
        break;
    }
    if(!judge->Check_CurrentIndex())
    {
        judge->SetTrueIndex();
    }
    else
    {
        //ui显示结果，暂停定时器
        Result();
        //显示最后一页
        ui->stackedWidget->setCurrentIndex(3);
    }

    //重置
    OneTime = 30;
}

void MyAnser::Result()
{
    OneTimerId->stop();
    judge->CloseTimer();

    ui->mscore_label_2->setText(QString::number(judge->GetScore()));
    ui->mscore_label_2->update();
    ui->mtime_label->setText(QString::number(judge->getTime()));
    ui->mtime_label->update();
    ui->ysore_label_2->setText(QString::number(yourscore));
    ui->ysore_label_2->update();
    ui->ytime_label->setText(QString::number(yourtime));
    ui->ytime_label->update();
}

void MyAnser::deal_recv_topix(QString stem, QString A, QString B, QString C, QString D, QString True)
{
    //题目存入容器中
    judge->SaveTopic(stem,A,B,C,D,True);

    //计入题目数量
    judge->SetTopicNum();

    //准备完毕，开始答题
    if(judge->CheckTopicNum())
    {
        deal_show();
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MyAnser::deal_your_true()
{
    yourscore += 20;
    ui->pscore_label->setText(QString::number(yourscore));
    ui->ysore_label_2->update();
}

void MyAnser::on_Back_Button_clicked()
{
    //通知widget打开主菜单
    emit do_MainWindow_show();
    this->close();
}

void MyAnser::on_OneMore_Button_clicked()
{
    //通知widget打开联机答题
    emit do_OnlineAnser_show();
    this->close();
}

void MyAnser::on_match_Button_clicked()
{
//    ui->stackedWidget->setCurrentIndex(1);
//    //服务器请求,联机答题
//    emit do_online_match();
    ui->stackedWidget->setCurrentIndex(3);
}

void MyAnser::on_A_Button_clicked()
{
    //无法点击其他选项
    ui->B_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);

    //检查A选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result(1);

    //保持1s
    deal_loop();

    qDebug() << "\n";

    //跳转下一题
    deal_show();
}

void MyAnser::on_B_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);
    //检查B选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result(2);

    //保持1s
    deal_loop();

    qDebug() << "\n";

    //跳转下一题
    deal_show();
}

void MyAnser::on_C_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->B_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);

    //检查C选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result(3);

    //保持1s
    deal_loop();

    qDebug() << "\n";

    //跳转下一题
    deal_show();
}

void MyAnser::on_D_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->B_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);

    //检查D选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result(4);

    //保持1s
    deal_loop();

    qDebug() << "\n";


    //跳转下一题
    deal_show();
}

