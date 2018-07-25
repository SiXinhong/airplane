#include "smallwidget.h"
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QColor>

SmallWidget::SmallWidget(int index, QWidget *parent) :
    QWidget(parent)
{
    //this->setStyleSheet(QString("background-color: rgb(255,0,0);"));
    gridLayout = new QGridLayout();
    upWidget = new QWidget(this);
    downWidget = new QWidget(this);
    upLabel = new QLabel(upWidget);
    downLabel = new QLabel(downWidget);

    gridLayout->addWidget(upWidget,0,0);
    gridLayout->addWidget(downWidget,1,0);


    gridLayout->setRowStretch(0, 1);
    gridLayout->setRowStretch(1, 1);

    this->setLayout(gridLayout);

    threadInterface = new SmallThread(index);
    threadInterface->start();
//    while(!threadInterface->isRun)
//        QThread::usleep(10);
    upLabel->setPixmap(threadInterface->getPixmap());
    downLabel->setPixmap(threadInterface->getPixmap());
    threadInterface->getNext();
    upLabel->setScaledContents(true);
    downLabel->setScaledContents(true);
}

SmallWidget::~SmallWidget(){
    threadInterface->exit();
    delete upLabel;
    delete upWidget;
    delete downLabel;
    delete downWidget;
    delete gridLayout;
}

void SmallWidget::setNumber(int num){
    this->number = num;
}

int SmallWidget::getNumber(){
    return this->number;
}

void SmallWidget::mousePressEvent(QMouseEvent *e){

}

void SmallWidget::mouseMoveEvent(QMouseEvent *e){

}

void SmallWidget::mouseReleaseEvent(QMouseEvent *e){

}

void SmallWidget::mouseDoubleClickEvent(QMouseEvent *e){
    int y = e->pos().y();
    if(y>this->height()/2){
        downScreen.label.setPixmap(*downLabel->pixmap());
        downScreen.show();
    }else{
        upScreen.label.setPixmap(*upLabel->pixmap());
        upScreen.show();
    }
}

void SmallWidget::resizeEvent(QResizeEvent *){
    upLabel->resize(upWidget->size());
    downLabel->resize(downWidget->size());
}

void SmallWidget::showNext(){
    QPixmap upmap = threadInterface->getPixmap();
    upLabel->setPixmap(upmap);
    upScreen.label.setPixmap(upmap);
    QPixmap downmap = threadInterface->getPixmap();
    downLabel->setPixmap(downmap);
    downScreen.label.setPixmap(downmap);
    threadInterface->getNext();
}
