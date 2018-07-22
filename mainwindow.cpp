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
#include "myinterface.h"
#include "smallthread.h"
#include "smallwidget.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* widget = new QWidget(this);

    //24个smallwidget
    sw11=new SmallWidget(widget);
    sw21=new SmallWidget(widget);
    sw31=new SmallWidget(widget);
    sw41=new SmallWidget(widget);
    sw51=new SmallWidget(widget);
    sw61=new SmallWidget(widget);
    sw71=new SmallWidget(widget);
    sw81=new SmallWidget(widget);
    sw91=new SmallWidget(widget);
    sw101=new SmallWidget(widget);
    sw111=new SmallWidget(widget);
    sw121=new SmallWidget(widget);

    sw12=new SmallWidget(widget);
    sw22=new SmallWidget(widget);
    sw32=new SmallWidget(widget);
    sw42=new SmallWidget(widget);
    sw52=new SmallWidget(widget);
    sw62=new SmallWidget(widget);
    sw72=new SmallWidget(widget);
    sw82=new SmallWidget(widget);
    sw92=new SmallWidget(widget);
    sw102=new SmallWidget(widget);
    sw112=new SmallWidget(widget);
    sw122=new SmallWidget(widget);

    //24个label
    label11=new QLabel(sw11);
    label21=new QLabel(sw21);
    label31=new QLabel(sw31);
    label41=new QLabel(sw41);
    label51=new QLabel(sw51);
    label61=new QLabel(sw61);
    label71=new QLabel(sw71);
    label81=new QLabel(sw81);
    label91=new QLabel(sw91);
    label101=new QLabel(sw101);
    label111=new QLabel(sw111);
    label121=new QLabel(sw121);

    label12=new QLabel(sw12);
    label22=new QLabel(sw22);
    label32=new QLabel(sw32);
    label42=new QLabel(sw42);
    label52=new QLabel(sw52);
    label62=new QLabel(sw62);
    label72=new QLabel(sw72);
    label82=new QLabel(sw82);
    label92=new QLabel(sw92);
    label102=new QLabel(sw102);
    label112=new QLabel(sw112);
    label122=new QLabel(sw122);

    //24个smallthread
    st11.start();
    st21.start();
    st31.start();
    st41.start();
    st51.start();
    st61.start();
    st71.start();
    st81.start();
    st91.start();
    st101.start();
    st111.start();
    st121.start();
    st12.start();
    st22.start();
    st32.start();
    st42.start();
    st52.start();
    st62.start();
    st72.start();
    st82.start();
    st92.start();
    st102.start();
    st112.start();
    st122.start();

    //1个bottomwidget
    bw = new BottomWidget(widget);

    //2个button
    QToolButton *left = new QToolButton(widget);
    left->setText(QString("<<<"));
    left->setToolTip("左移");
    connect(left,SIGNAL(clicked()),this,SLOT(moveLeft()));

    QToolButton *right = new QToolButton(widget);
    right->setText(QString(">>>"));
    right->setToolTip("右移");
    connect(right,SIGNAL(clicked()),this,SLOT(moveRight()));

    timer=new QTimer();
    timer->setInterval(1500);

    //布局
    gridlayout = new QGridLayout;
    gridlayout->addWidget(left,0,0);
    gridlayout->addWidget(sw11,0,1);
    gridlayout->addWidget(sw21,0,2);
    gridlayout->addWidget(sw31,0,3);
    gridlayout->addWidget(sw41,0,4);
    gridlayout->addWidget(sw51,0,5);
    gridlayout->addWidget(sw61,0,6);
    gridlayout->addWidget(sw12,1,1);
    gridlayout->addWidget(sw22,1,2);
    gridlayout->addWidget(sw32,1,3);
    gridlayout->addWidget(sw42,1,4);
    gridlayout->addWidget(sw52,1,5);
    gridlayout->addWidget(sw62,1,6);
    gridlayout->addWidget(sw71,2,1);
    gridlayout->addWidget(sw81,2,2);
    gridlayout->addWidget(sw91,2,3);
    gridlayout->addWidget(sw101,2,4);
    gridlayout->addWidget(sw111,2,5);
    gridlayout->addWidget(sw121,2,6);
    gridlayout->addWidget(sw72,3,0);
    gridlayout->addWidget(sw82,3,1);
    gridlayout->addWidget(sw92,3,2);
    gridlayout->addWidget(sw102,3,3);
    gridlayout->addWidget(sw112,3,4);
    gridlayout->addWidget(sw122,3,5);
    gridlayout->addWidget(right,3,6);

    gridlayout->addWidget(bw,4,0,1,7);

    gridlayout->setRowStretch(0, 1);
    gridlayout->setRowStretch(1, 1);
    gridlayout->setRowStretch(2, 1);
    gridlayout->setRowStretch(3, 1);
    gridlayout->setRowStretch(4, 1);

    gridlayout->setColumnStretch(0,1);
    gridlayout->setColumnStretch(1,1);
    gridlayout->setColumnStretch(2,1);
    gridlayout->setColumnStretch(3,1);
    gridlayout->setColumnStretch(4,1);
    gridlayout->setColumnStretch(5,1);
    gridlayout->setColumnStretch(6,1);

    widget->setLayout(gridlayout);
    this->setCentralWidget(widget);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimerOut(){

}

void MainWindow::moveLeft(){

}

void MainWindow::moveRight(){

}
