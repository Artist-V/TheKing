﻿#include <QApplication>
#include "myconnect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyConnect conn;

    return a.exec();
}

/*
 * MainWindow：主菜单（单机答题，联机答题）
 * 一次一共10题
 *
 * MyPaper：草稿纸
 *
 * MySingleAnser:单机答题
 * *加载离线题库
 * *写入答题容器
 * *定时器：答题、切换题目的时间
 * **槽函数：开始答题，定时器启动，题目显示
 * **槽函数：点击答案，对比答案与正确答案，正确（绿色）/错误（红色），答对（加分）/答错（不加分）
 * **槽函数：点击跳过，跳过题目，换到下一题
 * **槽函数：定时器时间到，切换下一题
 *
 * MyAnser:联机答题
 * MyLog:登录 / MyReg:注册
 * MyConnect:通信
 * *
 *
 *
 *
 *
 */

