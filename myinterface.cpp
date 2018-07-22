#include "myinterface.h"
#include <QTime>

MyInterface::MyInterface(int start)
{
    currentIndex = start;
}

QPixmap MyInterface::getPixmap(){
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);
    currentIndex = (currentIndex+qrand()%10)%24;
    return QPixmap(QString("./map/%1.jpg").arg(currentIndex));
}
