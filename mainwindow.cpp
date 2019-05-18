#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>

#include <QGridLayout>
#include <cv.h>

//OpenCV头文件
#include <vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include "cvutil.h"
#include "fullscreen.h"
#include "fullthread.h"
#include "smallwidget.h"
#include "objectdetection.h"
#include <QDebug>
#include <QTime>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConfigUtil::readConfigs();
    if(ConfigUtil::isOpenDetect || ConfigUtil::isOpenDetectLocal){
        ObjectDetection* od = ObjectDetection::getInstance();
        od->reconnect();
        od->createDetection();
        od->start();
    }
    QWidget* widget = new QWidget(this);
    gridlayout = new QGridLayout();
    this->setCentralWidget(widget);
    horizontalMove=2;
    for(int i=0;i<12;i++){
        sw1[i] = new SmallWidget(i,widget);
        sw2[i] = new SmallWidget(i+12,widget);
    }

    //1个bottomwidget
    bw = new QWidget(widget);

    timer=new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));

    this->BottomWidgetShow();
    isNeedAjustpicH = false;//设置成false不调整picH
    picH = 140;
    if(isNeedAjustpicH){
        picH=100;
        this->setLayout();
        lastDiff = 0;
        timer->setInterval(50);
    }else{
        this->setLayout();//调用自定义函数
    }

    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    QThread::sleep(2);//保证通信线程能预先通信完成，以免timerout积压，导致通信线程一直无效
    timer->start();
    qDebug()<<"start:"<<QTime::currentTime().toString("hh:mm:ss.zzz");
}

void MainWindow::setLayout(){
    //屏幕高度分成1000份，设置比例
    int h1=picH/6;//按钮默认是1/6图片高度
    int h2=picH*2;//一个sw包括upLabel和downLabel
    int h3=1000-h1*2-h2*2;//剩下的给bw
    QWidget *widget = new QWidget();//this->centralWidget();
    for(int i=0;i<12;i++){
        sw1[i]->setParent(NULL);
        sw2[i]->setParent(NULL);
    }
    bw->setParent(widget);
    //2个button
    QWidget *leftButtonWidget = new QWidget(widget);
    QWidget *rightButtonWidget = new QWidget(widget);
    QToolButton *left = new QToolButton(leftButtonWidget);
    left->setText(QString("<<<"));
    left->setToolTip("左移");
    connect(left,SIGNAL(clicked()),this,SLOT(moveLeft()));

    QToolButton *right = new QToolButton(rightButtonWidget);
    right->setText(QString(">>>"));
    right->setToolTip("右移");
    connect(right,SIGNAL(clicked()),this,SLOT(moveRight()));



    //布局
    //QGridLayout *gridlayout =(QGridLayout*) widget->layout();//new QGridLayout;
    gridlayout = new QGridLayout();
    gridlayout->addWidget(leftButtonWidget,0,0);
    for(int i=0;i<8;i++){
        sw1[horizontalMove+i]->setParent(widget);
        sw2[horizontalMove+i]->setParent(widget);
        gridlayout->addWidget(sw1[horizontalMove+i],1,i);
        gridlayout->addWidget(sw2[horizontalMove+i],2,i);
    }
    gridlayout->addWidget(rightButtonWidget,3,7);

    gridlayout->addWidget(bw,4,0,1,8);

    gridlayout->setRowStretch(0, h1);
    gridlayout->setRowStretch(1, h2);
    gridlayout->setRowStretch(2, h2);
    gridlayout->setRowStretch(3, h1);
    gridlayout->setRowStretch(4, h3);

    gridlayout->setColumnStretch(0,1);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,1);
    gridlayout->setColumnStretch(3,1);
    gridlayout->setColumnStretch(4,1);
    gridlayout->setColumnStretch(5,1);
    gridlayout->setColumnStretch(6,1);
    gridlayout->setColumnStretch(7,1);

    widget->setLayout(gridlayout);
    QWidget *lastWidget = this->centralWidget();
    QLayout *lastLayout = lastWidget->layout();
    this->setCentralWidget(widget);
    delete lastLayout;
    delete lastWidget;
    this->update();
}

MainWindow::~MainWindow()
{
    //timer->stop();
    //delete timer;
    delete ui;
    delete gridlayout;
    for(int i=0;i<12;i++){
        delete sw1[i];
        delete sw2[i];
    }
    delete bwLabel;
    delete bw;
    delete this->centralWidget();
}

void MainWindow::onTimerOut(){
    if(isNeedAjustpicH){
        double ratio = (double)sw1[6]->upLabel->height()/sw1[6]->upLabel->width();
        //与1080/1920=0.5625比较
        double diff = abs(ratio-0.5625);
        if(diff<=0.0001){
            isNeedAjustpicH=false;
            bwLabel->resize(bw->size());
            timer->setInterval(1500);
            qDebug()<<"picH1:"<<picH;
            return;
        }
        if(lastDiff != 0 && diff>lastDiff){
            isNeedAjustpicH=false;
            //diff比lastDiff大了，不再迭代了，恢复到上一次的picH
            picH--;
            this->setLayout();
            //需要下一行，否则bwLabel没有改变大小
            bwLabel->resize(bw->size());
            timer->setInterval(1500);
            qDebug()<<"picH2:"<<picH<<","<<lastDiff<<","<<diff;
            return;
        }
//        qDebug()<<"real:"<<picH<<","<<sw1[6]->upLabel->width()<<","<<sw1[6]->upLabel->height()<<","<<(double)sw1[6]->upLabel->height()/sw1[6]->upLabel->width();
        lastDiff = diff;
        //因为timerOut返回之前新的画面不会刷新，所以先判断上一次的diff，再让picH++
        picH++;//越大比例就越大
        this->setLayout();
        return;
    }
//    qDebug()<<"real:"<<picH<<","<<sw1[6]->upLabel->width()<<","<<sw1[6]->upLabel->height()<<","<<(double)sw1[6]->upLabel->height()/sw1[6]->upLabel->width();
    for(int i=0;i<12;i++){
        sw1[i]->showNext();
        sw2[i]->showNext();
    }
}

void MainWindow::moveLeft(){
    if(horizontalMove>0){
        horizontalMove--;
        this->setLayout();
    }else{
        QMessageBox::about(NULL, "提示", "到头了！");
    }

}

void MainWindow::moveRight(){
    if(horizontalMove<4){
        horizontalMove++;
        this->setLayout();
    }else{
        QMessageBox::about(NULL, "提示", "到头了！");
    }
}

void MainWindow::resizeEvent(QResizeEvent *){
    bwLabel->resize(bw->size());
}

void MainWindow::BottomWidgetShow(){
    bwLabel = new BottomLabel(bw);
    bwLabel->setScaledContents(true);
    QPixmap map("./map/map.jpg");
    //QPixmap map("./map/0.bmp");
    bwLabel->setPixmap(map);

}

