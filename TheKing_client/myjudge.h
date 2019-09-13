#ifndef MYJUDGE_H
#define MYJUDGE_H
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QTimer>
#include <QVector>

//题目数量
#define TitleNum 20

class MyJudge : public QObject
{
    Q_OBJECT
public:
    explicit MyJudge(QObject *parent = 0);

signals:

public slots://槽函数

     /*功能：处理AllTimer时间到*/
    void AllTimerUpdate();

public:
    /*功能：开启计时器*/
    void OpenTimer();

    /*功能：关闭计时器*/
    void CloseTimer();

    /*功能：输出时间*/
    int getTime();

    /*功能：存入题目*/
    void SaveTopic(QString,QString,QString,QString,QString,QString);

    /*功能：存入容器中*/
    QString TopicAt();
    QString qaAt();
    QString qbAt();
    QString qcAt();
    QString qdAt();
    int TrueAt();

    /*功能：变量自增1*/
    void SetTopicNum();
    void SetCurrentIndex();
    void SetTrueIndex();

    /*功能：取值*/
    int GetTopicNum();
    int GetScore();
    int GetCurrentIndex();
    int GetTrueIndex();

    /*功能：检查题目是否已接收完全*/
    bool CheckTopicNum();

    /*功能：检查题目是否已完成*/
    bool Check_CurrentIndex();

    /*功能：检查答案*/
    bool Check_Anser(int);

    //测试
    void test();

private:
    QVector<QString> topic;
    QVector<QString> qA;
    QVector<QString> qB;
    QVector<QString> qC;
    QVector<QString> qD;
    QVector<int> qTrue;

    int TopicNum;    //题目总数量
    int CurrentIndex; //当前题目
    int TrueIndex;   //当前正确答案
    int score;

    QTimer* AllTimerId;
    int AllTime;

public:

};

#endif // MYJUDGE_H
