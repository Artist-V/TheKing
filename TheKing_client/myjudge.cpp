#include "myjudge.h"
#include <QDebug>

MyJudge::MyJudge(QObject *parent) : QObject(parent)
{
    //初始化
    topic.clear();
    qA.clear();
    qB.clear();
    qC.clear();
    qD.clear();
    qTrue.clear();

    TopicNum = 0;
    CurrentIndex = 0;
    TrueIndex = 0;
    score = 0;

    AllTime = 0;
    AllTimerId = new QTimer(this);
    connect(AllTimerId,SIGNAL(timeout()),this,SLOT(AllTimerUpdate()));
}

void MyJudge::AllTimerUpdate()
{
    //计算总时间
    AllTime++;
}

void MyJudge::OpenTimer()
{
    AllTimerId->start(1000);
}

void MyJudge::CloseTimer()
{
    AllTimerId->stop();

}

int MyJudge::getTime()
{
    return AllTime;
}

void MyJudge::SaveTopic(QString stem, QString qa, QString qb, QString qc, QString qd, QString True)
{
    topic.push_back(stem);
    qA.push_back(qa);
    qB.push_back(qb);
    qC.push_back(qc);
    qD.push_back(qd);
    qTrue.push_back(True.toInt());

    qDebug() << "SaveTopic()" << stem  << "," << qa << "," << qb << "," << qc << "," << qd << "," << True.toInt();
}

QString MyJudge::TopicAt()
{
    qDebug() << "topic.at(CurrentIndex) = "<<topic.at(CurrentIndex);
    return topic.at(CurrentIndex);
}

QString MyJudge::qaAt()
{
    qDebug() << "qA.at(CurrentIndex) = " << qA.at(CurrentIndex);
    return qA.at(CurrentIndex);
}

QString MyJudge::qbAt()
{
    qDebug() << "qB.at(CurrentIndex) = " << qB.at(CurrentIndex);
    return qB.at(CurrentIndex);
}

QString MyJudge::qcAt()
{
    qDebug() << "qC.at(CurrentIndex) = " <<qC.at(CurrentIndex);
    return qC.at(CurrentIndex);
}

QString MyJudge::qdAt()
{
    qDebug() << "qD.at(CurrentIndex) = " << qD.at(CurrentIndex);
    return qD.at(CurrentIndex);
}

int MyJudge::TrueAt()
{
    qDebug() << "qTrue.at(CurrentIndex) = " << qTrue.at(CurrentIndex);
    return qTrue.at(CurrentIndex);
}

void MyJudge::SetTopicNum()
{
    TopicNum++;
    qDebug() << "TopicNum = " << TopicNum;
}

void MyJudge::SetCurrentIndex()
{
    CurrentIndex++;
    qDebug() << "CurrentIndex = " << CurrentIndex;
}

void MyJudge::SetTrueIndex()
{
    TrueIndex++;
    qDebug() << "TrueIndex = " << TrueIndex;
}

int MyJudge::GetTopicNum()
{
    return TopicNum;
}

bool MyJudge::CheckTopicNum()
{
    if(TopicNum == TitleNum)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int MyJudge::GetScore()
{
    return score;
}

int MyJudge::GetCurrentIndex()
{
    return CurrentIndex;
}

int MyJudge::GetTrueIndex()
{
    qDebug() << "GetTrueIndex()" << TrueIndex;

    return qTrue.at(TrueIndex);
}

bool MyJudge::Check_CurrentIndex()
{
    if(CurrentIndex == TitleNum)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyJudge::Check_Anser(int index)
{
    qDebug() << "Check_Anser(int index)" << TrueIndex;

    //答案正确
    if(qTrue.at(TrueIndex) == index)
    {
        score += 20;
        qDebug() << "score" << score;
        return true;
    }
    else
    {
        return false;
    }
}

void MyJudge::test()
{
    topic.push_back("以下不是构造函数特征的是");
    qA.push_back("构造函数的函数名与类名相同");
    qB.push_back("构造函数可以重载");
    qC.push_back("构造函数可以设置默认参数");
    qD.push_back("构造函数必须指定类型说明");
    qTrue.push_back(4);

    topic.push_back("下面关于友元函数描述正确的是");
    qA.push_back("友元函数的实现必须在类的内部定义");
    qB.push_back("友元函数是类的成员");
    qC.push_back("友元函数破坏了类的封装性和隐藏性");
    qD.push_back("友元函数不能访问类的私有成员");
    qTrue.push_back(3);

    topic.push_back("下面对静态数据成员的描述中，正确的是");
    qA.push_back("类的每一个对象都有自己的静态数据成员");
    qB.push_back("类的不同对象有不同的静态数据成员值");
    qC.push_back("静态数据成员不能通过类的对象调用");
    qD.push_back("静态数据成员是类的所有对象共享的数据");
    qTrue.push_back(4);

}

