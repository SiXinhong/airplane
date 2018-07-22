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
    this->setStyleSheet(QString("background-color: rgb(255,0,0);"));
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

    QPixmap p = QPixmap("./map/Lighthouse.jpg");
    QPixmap p1 = QPixmap("./map/Tulips.jpg");
    QPainter painter(&p);
    painter.setPen(QPen(QColor(index*20,0,index*20),200,Qt::SolidLine));
    painter.drawRect(0,0,200,200);
    upLabel->setPixmap(p);
    downLabel->setPixmap(p1);
    upLabel->setScaledContents(true);
    downLabel->setScaledContents(true);
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

void SmallWidget::resizeEvent(QResizeEvent *){
    upLabel->resize(upWidget->size());
    downLabel->resize(downWidget->size());
}

