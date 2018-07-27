#include "bottomlabel.h"
#include <QPainter>
#include<QMouseEvent>
#include<QDebug>
#include <QDesktopWidget>
#include<QApplication>
#include<QMessageBox>
#include <QDebug>

#include "mainwindow.h"

bool BottomLabel::is_draw = false;

BottomLabel::BottomLabel(QWidget *widget):QLabel(widget)
{
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(slotClicked()));

}
BottomLabel::~BottomLabel(){
    //timer->stop();
    //delete timer;
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
        //if(!timer->isActive())
        //    timer->start(300);
    this->is_draw = !this->is_draw;
    update();
}

void BottomLabel::mouseDoubleClickEvent(QMouseEvent *e){
    //timer->stop();
    //QLabel *zoom = new QLabel();
//    int posx = e->pos().x()*this->pixmap()->width()/this->width();
//    int posy = e->pos().y()*this->pixmap()->height()/this->height();
//    int width = this->pixmap()->width()/12;
//    int height = this->pixmap()->height()/2;
//    int x = posx/width*width;
//    int y = posy/height*height;

    //zoom->setPixmap(this->pixmap()->copy(x,y,width,height));
    //zoom->setWindowState(Qt::WindowMaximized);
    //zoom->setScaledContents(true);
    //zoom->show();
    //QMessageBox::about(NULL, "提示", "双击");
    MainWindow *mw = (MainWindow*)parentWidget()->parentWidget()->parentWidget();
    int posx = e->pos().x();
    int posy = e->pos().y();
    //qDebug()<<"posx:"<<posx<<";posy:"<<posy;
    if ((posx<this->width()/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[0]->upScreen.label.setPixmap(*mw->sw1[0]->upLabel->pixmap());
        mw->sw1[0]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[0]->upScreen.showFullScreen();
        mw->sw1[0]->upScreen.show();
    }
    else if ((posx<this->width()*2/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[1]->upScreen.label.setPixmap(*mw->sw1[1]->upLabel->pixmap());
        mw->sw1[1]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[1]->upScreen.showFullScreen();
        mw->sw1[1]->upScreen.show();
    }
    else if ((posx<this->width()*3/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[2]->upScreen.label.setPixmap(*mw->sw1[2]->upLabel->pixmap());
        mw->sw1[2]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[2]->upScreen.showFullScreen();
        mw->sw1[2]->upScreen.show();
    }
    else if ((posx<this->width()*4/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[3]->upScreen.label.setPixmap(*mw->sw1[3]->upLabel->pixmap());
        mw->sw1[3]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[3]->upScreen.showFullScreen();
        mw->sw1[3]->upScreen.show();
    }
    else if ((posx<this->width()*5/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[4]->upScreen.label.setPixmap(*mw->sw1[4]->upLabel->pixmap());
        mw->sw1[4]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[4]->upScreen.showFullScreen();
        mw->sw1[4]->upScreen.show();
    }
    else if ((posx<this->width()*6/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[5]->upScreen.label.setPixmap(*mw->sw1[5]->upLabel->pixmap());
        mw->sw1[5]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[5]->upScreen.showFullScreen();
        mw->sw1[5]->upScreen.show();
    }
    else if ((posx<this->width()*6/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[5]->upScreen.label.setPixmap(*mw->sw1[5]->upLabel->pixmap());
        mw->sw1[5]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[5]->upScreen.showFullScreen();
        mw->sw1[5]->upScreen.show();
    }
    else if ((posx<this->width()*7/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[6]->upScreen.label.setPixmap(*mw->sw1[6]->upLabel->pixmap());
        mw->sw1[6]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[6]->upScreen.showFullScreen();
        mw->sw1[6]->upScreen.show();
    }
    else if ((posx<this->width()*8/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[7]->upScreen.label.setPixmap(*mw->sw1[7]->upLabel->pixmap());
        mw->sw1[7]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[7]->upScreen.showFullScreen();
        mw->sw1[7]->upScreen.show();
    }
    else if ((posx<this->width()*9/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[8]->upScreen.label.setPixmap(*mw->sw1[8]->upLabel->pixmap());
        mw->sw1[8]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[8]->upScreen.showFullScreen();
        mw->sw1[8]->upScreen.show();
    }
    else if ((posx<this->width()*10/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[9]->upScreen.label.setPixmap(*mw->sw1[9]->upLabel->pixmap());
        mw->sw1[9]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[9]->upScreen.showFullScreen();
        mw->sw1[9]->upScreen.show();
    }
    else if ((posx<this->width()*11/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[10]->upScreen.label.setPixmap(*mw->sw1[10]->upLabel->pixmap());
        mw->sw1[10]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[10]->upScreen.showFullScreen();
        mw->sw1[10]->upScreen.show();
    }
    else if ((posx<this->width()*12/12)&&(posy<this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw1[11]->upScreen.label.setPixmap(*mw->sw1[11]->upLabel->pixmap());
        mw->sw1[11]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw1[11]->upScreen.showFullScreen();
        mw->sw1[11]->upScreen.show();
    }
    //bellow
    if ((posx<this->width()/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[0]->upScreen.label.setPixmap(*mw->sw2[0]->upLabel->pixmap());
        mw->sw2[0]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[0]->upScreen.showFullScreen();
        mw->sw2[0]->upScreen.show();
    }
    else if ((posx<this->width()*2/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[1]->upScreen.label.setPixmap(*mw->sw2[1]->upLabel->pixmap());
        mw->sw2[1]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[1]->upScreen.showFullScreen();
        mw->sw2[1]->upScreen.show();
    }
    else if ((posx<this->width()*3/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[2]->upScreen.label.setPixmap(*mw->sw2[2]->upLabel->pixmap());
        mw->sw2[2]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[2]->upScreen.showFullScreen();
        mw->sw2[2]->upScreen.show();
    }
    else if ((posx<this->width()*4/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[3]->upScreen.label.setPixmap(*mw->sw2[3]->upLabel->pixmap());
        mw->sw2[3]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[3]->upScreen.showFullScreen();
        mw->sw2[3]->upScreen.show();
    }
    else if ((posx<this->width()*5/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[4]->upScreen.label.setPixmap(*mw->sw2[4]->upLabel->pixmap());
        mw->sw2[4]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[4]->upScreen.showFullScreen();
        mw->sw2[4]->upScreen.show();
    }
    else if ((posx<this->width()*6/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[5]->upScreen.label.setPixmap(*mw->sw2[5]->upLabel->pixmap());
        mw->sw2[5]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[5]->upScreen.showFullScreen();
        mw->sw2[5]->upScreen.show();
    }
    else if ((posx<this->width()*6/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[5]->upScreen.label.setPixmap(*mw->sw2[5]->upLabel->pixmap());
        mw->sw2[5]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[5]->upScreen.showFullScreen();
        mw->sw2[5]->upScreen.show();
    }
    else if ((posx<this->width()*7/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[6]->upScreen.label.setPixmap(*mw->sw2[6]->upLabel->pixmap());
        mw->sw2[6]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[6]->upScreen.showFullScreen();
        mw->sw2[6]->upScreen.show();
    }
    else if ((posx<this->width()*8/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[7]->upScreen.label.setPixmap(*mw->sw2[7]->upLabel->pixmap());
        mw->sw2[7]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[7]->upScreen.showFullScreen();
        mw->sw2[7]->upScreen.show();
    }
    else if ((posx<this->width()*9/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[8]->upScreen.label.setPixmap(*mw->sw2[8]->upLabel->pixmap());
        mw->sw2[8]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[8]->upScreen.showFullScreen();
        mw->sw2[8]->upScreen.show();
    }
    else if ((posx<this->width()*10/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[9]->upScreen.label.setPixmap(*mw->sw2[9]->upLabel->pixmap());
        mw->sw2[9]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[9]->upScreen.showFullScreen();
        mw->sw2[9]->upScreen.show();
    }
    else if ((posx<this->width()*11/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[10]->upScreen.label.setPixmap(*mw->sw2[10]->upLabel->pixmap());
        mw->sw2[10]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[10]->upScreen.showFullScreen();
        mw->sw2[10]->upScreen.show();
    }
    else if ((posx<this->width()*12/12)&&(posy>this->height()/2)){
        //QMessageBox::about(NULL, "提示", "左上角");
        mw->sw2[11]->upScreen.label.setPixmap(*mw->sw2[11]->upLabel->pixmap());
        mw->sw2[11]->upScreen.setWindowFlags(Qt::WindowStaysOnTopHint);
        mw->sw2[11]->upScreen.showFullScreen();
        mw->sw2[11]->upScreen.show();
    }
}

//void BottomLabel::slotClicked(){
//    timer->stop();
//    is_draw = ! is_draw;
//    update();
//}
