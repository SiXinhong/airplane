#include "fullscreen.h"

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

using namespace cv;
using namespace std;

FullScreen::FullScreen(QWidget *parent) :
    QMainWindow(parent)
{
    label.setParent(this);
    label.setScaledContents(true);
}

FullScreen::~FullScreen(){

}

void FullScreen::setNumber(int num){
    this->number = num;
}

int FullScreen::getNumber(){
    return this->number;
}

void FullScreen::resizeEvent(QResizeEvent *){
    label.resize(this->size());
}
