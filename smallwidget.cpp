#include "smallwidget.h"
#include <QPoint>
#include <QMouseEvent>

SmallWidget::SmallWidget(QWidget *parent) :
    QWidget(parent)
{
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

}

