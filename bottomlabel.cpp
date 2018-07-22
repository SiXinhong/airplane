#include "bottomlabel.h"
#include <QPainter>
#include<QMouseEvent>
#include<QDebug>
#include <QDesktopWidget>
#include<QApplication>

bool BottomLabel::is_draw = false;

BottomLabel::BottomLabel(QWidget *widget):QLabel(widget)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotClicked()));

}
BottomLabel::~BottomLabel(){
    timer->stop();
    delete timer;
}

void BottomLabel::paintEvent(QPaintEvent *e){
    QLabel::paintEvent(e);
    if(is_draw){
        QPainter p(this);
        p.setPen(Qt::red);
        p.drawLine(QPoint(this->x(),this->height()/2),QPoint(this->width(),this->height()/2));
        for(int i =1;i<12;i++){
            p.drawLine(QPoint(this->width()/12*i,this->y()),QPoint(this->width()/12*i,this->height()));
        }
    }
}

void BottomLabel::mousePressEvent(QMouseEvent *e){
        if(!timer->isActive())
            timer->start(300);
}

void BottomLabel::mouseDoubleClickEvent(QMouseEvent *e){
    timer->stop();
    QLabel *zoom = new QLabel();
    int posx = e->pos().x()*this->pixmap()->width()/this->width();
    int posy = e->pos().y()*this->pixmap()->height()/this->height();
    int width = this->pixmap()->width()/12;
    int height = this->pixmap()->height()/2;
    int x = posx/width*width;
    int y = posy/height*height;
    zoom->setPixmap(this->pixmap()->copy(x,y,width,height));
    //zoom->setWindowState(Qt::WindowMaximized);
    zoom->setScaledContents(true);
    zoom->show();
}

void BottomLabel::slotClicked(){
    timer->stop();
    is_draw = ! is_draw;
    update();
}
