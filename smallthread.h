#ifndef SMALLTHREAD_H
#define SMALLTHREAD_H

#include <QThread>
#include <QPixmap>
#include <QMutex>
#include <QWaitCondition>
#include "myinterface.h"

class SmallThread: public QThread
{

private:
    int number;
    MyInterface *interface;

public:
    SmallThread(int number);
    ~SmallThread();
    void run();
    void setNumber(int num);
    int getNumber();
    bool isOk;//通信是否已经结束，可以取出QPixmap
    QMutex mutex;
    QWaitCondition fullCond;
    QWaitCondition emptyCond;
    void getNext();
    QPixmap getPixmap();
    QPixmap pixmap;
    volatile bool isRun;//调用线程start()后，不一定立即执行，用这个判断是否执行了，以免出现死锁
};

#endif // SMALLTHREAD_H
