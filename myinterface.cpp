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
    QPainter painter(&pixmap);
    QPen pen;
    pen.setBrush(Qt::white);
    painter.setPen(pen);
    int w = pixmap.width();
    int h = pixmap.height();
    painter.drawLine(w/2 - 10, h/2, w/2 + 10, h/2);
    painter.drawLine(w/2, h/2 - 10, w/2, h/2 + 10);
    this->pixmap = pixmap;
}

QPixmap MyInterface::getPixmap(){
    currentIndex = (currentIndex+qrand()%10)%50;
    return cache.at(currentIndex);
}

void MyInterface::onDetectionFinish(QString filename, vector<ObjectItem> items){
    qDebug()<<"onDetectionFinish";
    mutex.lock();
    this->pixmap = QPixmap(this->dirName);
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
        painter.drawRect(QRect(items[i].startPoint,items[i].endPoint));
    }
    this->imageStatus = 2;
    waitCondition.wakeAll();
    mutex.unlock();
    qDebug()<<"onDetectionFinish2";
}
