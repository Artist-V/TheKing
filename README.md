# TheKing

# 过程中遇到的问题和解决方法
1. 本来是把每个界面都封装成了一个类，然后网络通信是一个类，数据库是一个类，但是类与类之间的实现使用对象指针来实现的，其实这样做法有点破坏了类的封装，而且在构造函数实现构造对象的时候也要初始化对象指针。造成了类与类之间的耦合度变高了。所以后面改成了多线程来做通信，新建线程MyThread继承QThread，在线程中实现网络通信。


2. 为什么用对象指针不用对象本身？

A：我个人的理解是，对象本身的话也可以，这样在创建局部对象，调用show()之后，要调用exec()函数，让他一直循环调用窗口。因为对象是局部变量，存在栈数据区，在函数调用结束之后就回收资源了。而对象指针是由程序员动态内存分配的，存在堆数据区，需要程序员手动释放的时候才释放所以窗口对象指针调用show()函数，窗口会一直存在


3. 无法为位于不同线程中的父对象创建子对象
>QObject: Cannot create children for a parent that is in a different thread.
(Parent is QTcpSocket(0x28b45861430), parent's thread is QThread(0x28b4374d920), current thread is MyThread(0x28b43801d10)
QObject: Cannot create children for a parent that is in a different thread.
(Parent is QTcpSocket(0x28b45861430), parent's thread is QThread(0x28b4374d920), current thread is MyThread(0x28b43801d10)

解决方法：将初始化也放在run函数中【因为传入this指针相当于在子线程里为主线程建立了对象，所以出现跨线程警告。QT中继承Qthread类后,在类中定义的对象或对象指针都是属于主线程的。次线程正真意义上的实体内容实在实现run()函数里。所以，要将mythread线程里的对象或指针创建，需要在run()函数里,创建或分配对象空间。】


4. 无法从另一个线程启用或禁用套接字通知程序
>QSocketNotifier: Socket notifiers cannot be enabled or disabled from another thread
ASSERT failure in QCoreApplication::sendEvent: "Cannot send events to objects owned by a different thread. Current thread 218e5f2b4d0. Receiver '' (of type 'QNativeSocketEngine') was created in thread 218e5f85670", file kernel\qcoreapplication.cpp, line 541

错误背景：想按下“关闭服务器”，服务器就停止监听
解决方法：


5. qt 按钮变灰
A：pushButton->setEnabled(false);


6. 返回套接字的状态
* QAbstractSocket::state() const
| constant | value | description |
| :------: | :---: | :---------: |
| QAbstractSocket::UnconnectedState | 0 | 插座未连接 |
| QAbstractSocket::HostLookupState | 1 | 套接字正在执行主机名查找 |
| QAbstractSocket::ConnectingState | 2 | 套接字已开始建立连接 |
| QAbstractSocket::ConnectedState | 3 | 建立了连接 |
| QAbstractSocket::BoundState | 4 | 套接字绑定到一个地址和端口 |
| QAbstractSocket::ClosingState | 6 | 套接字即将关闭(数据可能仍在等待写入) |
| QAbstractSocket::ListeningState | 5 | 内部使用 |


7.Qt中想使用QString类型的switch/case结构

可以用QStringList来实现
```
  QStringList option ;
  option << "A" << "B" << "C" << "D";

  QString True = qTrue.at(TrueIndex);

  switch (option.indexOf(True))
  {
  case 0:
      ui->A_Button->setStyleSheet();
      break;
  case 1:
      break;
  case 2:
      break;
  case 3:
      break;
  }

```


8. Qt主线程循环
* Qt一般使用QThread::sleep()来延时，但是这样会阻塞住线程，ui也会停着不动
* 事件循环 <===>  防止界面卡死
  * 类似于一个事件队列，对列入的事件依次的进行处理，当时间做完而时间循环没有结束的时候，其实际上比较类似于一个不占用CPU事件的for(;;)循环
  * 程序在exec()里面无限循环，能让跟在exec()后面的代码得不到运行机会，直至程序从exec()跳出。从exec()跳出时，事件循环即被终止。QEventLoop::quit()能够终止事件循环
  * QEventLoop::exec()的时候，虽然这些exec()打断了main()中的QApplication::exec()，但是由于GUI界面的响应已经被包含到子循环中了，所以GUI界面依然能够得到响应
  * 调用传统的Sleep，这时候程序会阻塞；所以开启本地事件循环，搭配QTimer::singleShot(int msec, const QObject * receiver, const char * member) 静态函数会在给定的时间间隔之后调用一个member槽函数。（时间间隔为msec毫秒）


