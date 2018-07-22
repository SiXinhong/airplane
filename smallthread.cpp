#include "smallthread.h"
#include "myinterface.h"

SmallThread::SmallThread(int number)
{
    setNumber(number);
    interface = new MyInterface(number);
    isOk = false;
    isRun = false;
}

void SmallThread::run(){
    isRun = true;
    while(true){
        mutex.lock();
        fullCond.wait(&mutex);
        pixmap = interface->getPixmap();
        isOk = true;
        emptyCond.wakeAll();
        mutex.unlock();
    }
}

void SmallThread::setNumber(int num){
    this->number = num;
}

int SmallThread::getNumber(){
    return this->number;
}

QPixmap SmallThread::getPixmap(){
    mutex.lock();
    while(!isOk)
    {
        fullCond.wakeAll();
        emptyCond.wait(&mutex);
    }
    isOk = false;
    mutex.unlock();
    return pixmap;
}

// 如果这个地方比run()运行的早，那么会死锁，所以用isRun来判断下已经执行到run了才能调用这个函数
void SmallThread::getNext(){
    mutex.lock();
    fullCond.wakeAll();
    mutex.unlock();
}
