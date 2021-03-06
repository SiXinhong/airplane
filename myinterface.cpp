#include "myinterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "cvutil.h"
#include <QPainter>
#include <QPen>

MyInterface* MyInterface::interfaces[24];

MyInterface::MyInterface(int start)
{
    currentIndex = start;
    this->objectDetection = ObjectDetection::getInstance();
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }

    this->isLogin = false;

    QDir dir;
    this->dirName = QString("./image/%1").arg(this->currentIndex);
    if(!dir.exists(dirName)){
        qDebug()<<"mkdir:"<<dir.mkdir(dirName)<<",dirName:"<<dirName;
    }
    dirName = dirName.append("/tmp.jpg");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);

    this->imageStatus = -1;
}

MyInterface::MyInterface(int start,QString ip,QString userName,QString passwd,int port){
    this->objectDetection = ObjectDetection::getInstance();
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
    currentIndex = start;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }

    this->isLogin = false;
}

void MyInterface::setLogin(QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
}
void MyInterface::setPixMap(QPixmap pixmap){
    int w = pixmap.width();
    int h = pixmap.height();
    int a = h/2;
    QPainter painter(&pixmap);
    QPen pen;
    pen.setBrush(Qt::black);
    painter.setPen(pen);

    // 正方形
    painter.drawRect(w/2 - a/2, h/2 - a/2, a, a);
    painter.drawLine(w/2 - a/2, h/2 - a/2, w/2 + a/2, h/2 + a/2);
    painter.drawLine(w/2 - a/2, h/2 + a/2, w/2 + a/2, h/2 - a/2);

    pen.setBrush(Qt::blue);
    painter.setPen(pen);
    int dist = w/30;
    painter.drawLine(2*dist, h/2, w-2*dist, h/2);
    painter.drawLine(w/2, 2*dist, w/2, h-2*dist);

    int wCount = (w/2-3*dist)/dist;
    int wStart = w/2 - wCount*dist;
    int y1 = h/2 - dist;
    int y2 = h/2 + dist;
    int cnt = 0;
    for(int x = wStart; cnt<2*wCount;cnt++,x+=dist){
        painter.drawLine(x, y1, x, y2);
    }
    int hCount = (h/2-3*dist)/dist;
    int hStart = h/2 - hCount*dist;
    int x1 = w/2 - dist;
    int x2 = w/2 + dist;
    cnt = 0;
    for(int y = hStart; cnt<2*hCount; cnt++,y+=dist){
        painter.drawLine(x1, y, x2, y);
    }
    this->pixmap = pixmap;
}

QPixmap MyInterface::getPixmap(){
    if(!ConfigUtil::isOpenDetectLocal){
        currentIndex = (currentIndex+qrand()%10)%50;
        return cache.at(currentIndex);
    }else{
        //开启检测时，取缓存，且添加下一个被检测的图片
        mutex.lock();
        int count = 0;
        while(this->imageStatus != 2 && count < 5)
        {
            count++;
            waitCondition.wait(&mutex,50);
        }
        if(this->imageStatus == 2){
            currentIndex = (currentIndex+qrand()%10)%50;
            this->dirName = QString("./image/%1.jpg").arg(currentIndex);
            this->objectDetection->detection(DetectionPair(this,QString("../")+this->dirName));
            this->imageStatus = 1;// 设置为正在被检测
        }
        mutex.unlock();
        return pixmap;
    }
}

void MyInterface::onDetectionFinish(QString filename, vector<ObjectItem> items){
    qDebug()<<"onDetectionFinish";
    mutex.lock();
    this->pixmap = QPixmap(filename.right(filename.length()-3));
    if(items.empty()){
        qDebug()<<"onDetectionFinish1";
        this->imageStatus = 2;
        mutex.unlock();
        return;
    }
    int count = items.size();
    QPainter painter(&pixmap);
    for (int i = 0; i < count; i++){
//        qDebug()<<"filename:"<<filename<<","<<items[i].name;
        if(items[i].name == "car" || items[i].name == "person"){
            painter.drawRect(QRect(items[i].startPoint,items[i].endPoint));
        }
    }
    this->imageStatus = 2;
    waitCondition.wakeAll();
    mutex.unlock();
    qDebug()<<"onDetectionFinish2";
}
