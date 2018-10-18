#include "smallthread.h"
#include "myinterface.h"

SmallThread::SmallThread(int number)
{
    setNumber(number);
    inter = new MyInterface(number);
    isOk = false;
    isRun = false;
    if(number == 5){
        inter->setLogin(QString("192.168.1.2"),QString("testusername"),QString("testpasswd"),9000);
        for(int i=0;!inter->isLogin && i<5;i++){
            inter->login();
        }
    }
}
SmallThread::~SmallThread(){
    delete inter;
}

void SmallThread::run(){
    isRun = true;
    while(true){
        mutex.lock();
        fullCond.wait(&mutex);
        pixmap = inter->getPixmap();
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
        emptyCond.wait(&mutex,50);//第二个参数是等待50毫秒，如果没有信号通知，就直接返回，防止死锁。因为有while循环，所以会重试
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
