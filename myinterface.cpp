#include "myinterface.h"
#include <QTime>

MyInterface::MyInterface(int start)
{
    currentIndex = start;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }
}

QPixmap MyInterface::getPixmap(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);
    currentIndex = (currentIndex+qrand()%10)%50;
    //return QPixmap(QString("./image/%1.jpg").arg(currentIndex));
    return cache.at(currentIndex);
}
