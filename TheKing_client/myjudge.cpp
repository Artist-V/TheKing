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


    //void MyJudge::test()
    //{
    //    topic.push_back("111");
    //    qA.push_back("111");
    //    qB.push_back("111");
    //    qC.push_back("111");
    //    qD.push_back("111");
    //    qTrue.push_back(1);

    //    topic.push_back("222");
    //    qA.push_back("222");
    //    qB.push_back("222");
    //    qC.push_back("222");
    //    qD.push_back("222");
    //    qTrue.push_back(2);

    //    topic.push_back("333");
    //    qA.push_back("333");
    //    qB.push_back("333");
    //    qC.push_back("333");
    //    qD.push_back("333");
    //    qTrue.push_back(3);

    //}

