#include "mysingleanser.h"
#include "ui_mysingleanser.h"
#include <QTimer>

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
    TopicNum = 0;
    CurrenIndex = 0;
    TrueIndex = 0;
    option << "A" << "B" << "C" << "D";

//测试
    topic.push_back("111");
    qA.push_back("111");
    qB.push_back("111");
    qC.push_back("111");
    qD.push_back("111");
    qTrue.push_back("A");

    topic.push_back("222");
    qA.push_back("222");
    qB.push_back("222");
    qC.push_back("222");
    qD.push_back("222");
    qTrue.push_back("B");

    topic.push_back("333");
    qA.push_back("333");
    qB.push_back("333");
    qC.push_back("333");
    qD.push_back("333");
    qTrue.push_back("C");

    deal_show();
    ui->stackedWidget->setCurrentIndex(2);
}

MySingleAnser::~MySingleAnser()
{
    delete ui;
}

void MySingleAnser::on_start_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    //服务器请求,单机答题
    emit do_single_start();
}

void MySingleAnser::on_A_Button_clicked()
{
    //无法点击其他选项
    ui->B_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);

    //检查A选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result();

    //保持1s
    //QThread::sleep(2);
    deal_loop();

    //跳转下一题
    deal_show();
}

void MySingleAnser::on_B_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);
    //检查B选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result();

    //保持1s
    //QThread::sleep(2);
    deal_loop();

    //跳转下一题
    deal_show();
}

void MySingleAnser::on_C_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->B_Button->setEnabled(false);
    ui->D_Button->setEnabled(false);

    //检查C选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result();

    //保持1s
    //QThread::sleep(2);
    deal_loop();

    //跳转下一题
    deal_show();
}

void MySingleAnser::on_D_Button_clicked()
{
    //无法点击其他选项
    ui->A_Button->setEnabled(false);
    ui->B_Button->setEnabled(false);
    ui->C_Button->setEnabled(false);

    //检查D选项是否正确
    //更改样式表（正确：红色；错误：绿色）
    deal_button_result();

    //保持1s
    //QThread::sleep(2);
    deal_loop();


    //跳转下一题
    deal_show();
}

void MySingleAnser::on_End_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MySingleAnser::on_BackButton_clicked()
{
    //通知widget打开主菜单
    emit do_MainWindow_show();
    this->close();
}

void MySingleAnser::on_OneMoreButton_clicked()
{
    //通知widget打开单机答题
    emit do_SingleAnser_show();
    this->close();
}

void MySingleAnser::deal_single_start(QString stem,QString A,QString B,QString C,QString D,QString True)
{
    //题目存入容器中
    topic.push_back(stem);
    qA.push_back(A);
    qB.push_back(B);
    qC.push_back(C);
    qD.push_back(D);
    qTrue.push_back(True);

    //计入题目数量
    TopicNum++;

    //准备完毕，开始答题
    if(TopicNum == TitleNum)
    {
        deal_show();
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MySingleAnser::deal_show()
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

    //题目更换
    ui->topic_textEdit->setText(topic.at(CurrenIndex));
    ui->A_Button->setText(qA.at(CurrenIndex));
    ui->B_Button->setText(qB.at(CurrenIndex));
    ui->C_Button->setText(qC.at(CurrenIndex));
    ui->D_Button->setText(qD.at(CurrenIndex));

    CurrenIndex++;
}

void MySingleAnser::deal_loop()
{
    QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();
}

void MySingleAnser::deal_button_result()
{
    //显示正确答案
    QString True = qTrue.at(TrueIndex);

    switch (option.indexOf(True))
    {
    case 0:
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->A_Button->update();
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->B_Button->update();
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->C_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 1:
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->B_Button->update();
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->A_Button->update();
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->C_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 2:
        ui->C_Button->setStyleSheet("QPushButton{background-color: rgb(0,255,0)}");
        ui->C_Button->update();
        ui->A_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->A_Button->update();
        ui->B_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->B_Button->update();
        ui->D_Button->setStyleSheet("QPushButton{background-color: rgb(255,0,0)}");
        ui->D_Button->update();
        break;
    case 3:
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
    TrueIndex++;
}

