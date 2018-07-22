#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QToolButton>

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
#include "bottomlabel.h"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setLayout();
    //24个label
//    QLabel *label11;
//    QLabel *label21;
//    QLabel *label31;
//    QLabel *label41;
//    QLabel *label51;
//    QLabel *label61;
//    QLabel *label71;
//    QLabel *label81;
//    QLabel *label91;
//    QLabel *label101;
//    QLabel *label111;
//    QLabel *label121;

//    QLabel *label12;
//    QLabel *label22;
//    QLabel *label32;
//    QLabel *label42;
//    QLabel *label52;
//    QLabel *label62;
//    QLabel *label72;
//    QLabel *label82;
//    QLabel *label92;
//    QLabel *label102;
//    QLabel *label112;
//    QLabel *label122;

    //加载到24个QLabel上的24个QImage
    QImage imgLabel11;
    QImage imgLabel21;
    QImage imgLabel31;
    QImage imgLabel41;
    QImage imgLabel51;
    QImage imgLabel61;
    QImage imgLabel71;
    QImage imgLabel81;
    QImage imgLabel91;
    QImage imgLabel101;
    QImage imgLabel111;
    QImage imgLabel121;

    QImage imgLabel12;
    QImage imgLabel22;
    QImage imgLabel32;
    QImage imgLabel42;
    QImage imgLabel52;
    QImage imgLabel62;
    QImage imgLabel72;
    QImage imgLabel82;
    QImage imgLabel92;
    QImage imgLabel102;
    QImage imgLabel112;
    QImage imgLabel122;

    //24个smallwidget
//    SmallWidget *sw11;
//    SmallWidget *sw21;
//    SmallWidget *sw31;
//    SmallWidget *sw41;
//    SmallWidget *sw51;
//    SmallWidget *sw61;
//    SmallWidget *sw71;
//    SmallWidget *sw81;
//    SmallWidget *sw91;
//    SmallWidget *sw101;
//    SmallWidget *sw111;
//    SmallWidget *sw121;
//    SmallWidget *sw12;
//    SmallWidget *sw22;
//    SmallWidget *sw32;
//    SmallWidget *sw42;
//    SmallWidget *sw52;
//    SmallWidget *sw62;
//    SmallWidget *sw72;
//    SmallWidget *sw82;
//    SmallWidget *sw92;
//    SmallWidget *sw102;
//    SmallWidget *sw112;
//    SmallWidget *sw122;

    SmallWidget* sw1[12];
    SmallWidget* sw2[12];
    int horizontalMove;//从第几个sw开始显示[0,4]
    //24个samllthread
    SmallThread st11;
    SmallThread st21;
    SmallThread st31;
    SmallThread st41;
    SmallThread st51;
    SmallThread st61;
    SmallThread st71;
    SmallThread st81;
    SmallThread st91;
    SmallThread st101;
    SmallThread st111;
    SmallThread st121;
    SmallThread st12;
    SmallThread st22;
    SmallThread st32;
    SmallThread st42;
    SmallThread st52;
    SmallThread st62;
    SmallThread st72;
    SmallThread st82;
    SmallThread st92;
    SmallThread st102;
    SmallThread st112;
    SmallThread st122;

    //1个BottomWidget
    QWidget *bw;
    BottomLabel *bwLabel;

    //2个button
    QToolButton * left;
    QToolButton * right;

    QTimer *timer;

    QGridLayout *gridlayout;

private:
    Ui::MainWindow *ui;

public:
    void BottomWidgetShow();

public slots:
  void onTimerOut();
  void moveLeft();
  void moveRight();
  void resizeEvent(QResizeEvent *);
};

#endif // MAINWINDOW_H
