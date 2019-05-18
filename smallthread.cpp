#include "smallthread.h"
#include "myinterface.h"
#include "configutil.h"

SmallThread::SmallThread(int number)
{
    setNumber(number);
    if(ConfigUtil::isOpenCam[number] == 1){
        inter = new HkInterface(number);
    }else{
        inter = new DahuaInterface(number);
    }
    isOk = false;
    isRun = false;
    if(ConfigUtil::isOpenCam[number] != 0){
        inter->setLogin(ConfigUtil::ip[number], ConfigUtil::user[number],
                        ConfigUtil::passwd[number], ConfigUtil::port[number]);
        for(int i=0;!inter->isLogin && i<5;i++){
            inter->login();
        }
    }else{
        //使用本地图片时，如果检测，先添加检测图片
        if(ConfigUtil::isOpenDetectLocal){
            inter->imageStatus = 1;// 设置为正在被检测
            inter->dirName = QString("./image/0.jpg");
            inter->objectDetection->detection(DetectionPair(inter,QString("../")+inter->dirName));
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
    int count = 0;
    while(!isOk && count < 5)
    {
        count++;//不无限等待
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
