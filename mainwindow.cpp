#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>

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
#include <QDebug>

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* widget = new QWidget(this);
    gridlayout = new QGridLayout();
    this->setCentralWidget(widget);
    horizontalMove=2;
    for(int i=0;i<12;i++){
        sw1[i] = new SmallWidget(i,widget);
        sw2[i] = new SmallWidget(i,widget);
    }

    //1个bottomwidget
    bw = new QWidget(widget);

    timer=new QTimer();
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), SLOT(onTimerOut()));
    timer->start();
    this->BottomWidgetShow();
this->setLayout();//调用自定义函数
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

void MainWindow::setLayout(){
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

    gridlayout->setRowStretch(0, 1);
    gridlayout->setRowStretch(1, 6);
    gridlayout->setRowStretch(2, 6);
    gridlayout->setRowStretch(3, 1);
    gridlayout->setRowStretch(4, 6);

    gridlayout->setColumnStretch(0,1);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,1);
    gridlayout->setColumnStretch(3,1);
    gridlayout->setColumnStretch(4,1);
    gridlayout->setColumnStretch(5,1);
    gridlayout->setColumnStretch(6,1);
    gridlayout->setColumnStretch(7,1);

    widget->setLayout(gridlayout);
    this->setCentralWidget(widget);
    this->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimerOut(){
    for(int i=0;i<12;i++){
        sw1[i]->showNext();
        sw2[i]->showNext();
    }
}

void MainWindow::moveLeft(){
    if(horizontalMove>0){
        horizontalMove--;
        this->setLayout();
    }
}

void MainWindow::moveRight(){
    if(horizontalMove<4){
        horizontalMove++;
        this->setLayout();
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

