#include "dahuainterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>
#include "dhplay.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "cvutil.h"
#include <QPainter>

DahuaInterface::DahuaInterface(int start):MyInterface(start)
{
    // 初始化
    CLIENT_LogClose();
    CLIENT_Init(NULL, 0);
    //设置重连
}

DahuaInterface::DahuaInterface(int start,QString ip,QString userName,QString passwd,int port)
    :MyInterface(start, ip, userName, passwd, port){
    // 初始化
    CLIENT_LogClose();
    CLIENT_Init(NULL, 0);
    //设置重连
}

//数据解码回调函数，
//功能：将YV_12格式的视频数据流转码为可供opencv处理的BGR类型的图片数据
void CALLBACK DecCBFun1(long nPort, char* pBuf, long nSize, FRAME_INFO* pFrameInfo, void* nUser, long nReserved2)
{
//    qDebug()<<"解码回调"<<pFrameInfo->nType;
    if (pFrameInfo->nType == 3)
    {
        MyInterface::interfaces[nPort]->mutex.lock();
        // 正在被检测
        if(MyInterface::interfaces[nPort]->imageStatus == 1 || MyInterface::interfaces[nPort]->imageStatus == -1){
            MyInterface::interfaces[nPort]->mutex.unlock();
            return;
        }
//        qDebug()<<"DecCBFun"<<MyInterface::interfaces[nPort]->imageStatus;
        //qDebug()<< "the frame infomation is T_YV12";
        cv::Mat g_BGRImage;
        g_BGRImage.create(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
        cv::Mat YUVImage(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, (unsigned char*)pBuf);

        cv::cvtColor(YUVImage, g_BGRImage, cv::COLOR_YUV2BGR_YV12);
        //QString dir =  QString("./image/port/%1").arg(nPort).append("/tmp.jpg");
        //cv::imwrite(dir.toStdString(),g_BGRImage);
        //qDebug()<< "write image to "<<dir;
        if(!ConfigUtil::isOpenDetect){
            MyInterface::interfaces[nPort]->setPixMap(CVUtil::cvMatToQPixmap(g_BGRImage));
        }else{
            cv::imwrite(MyInterface::interfaces[nPort]->dirName.toStdString(),g_BGRImage);
            //qDebug()<< "write image to "<<interfaces[nPort]->dirName;
            MyInterface::interfaces[nPort]->imageStatus = 1;// 设置为正在被检测
            MyInterface::interfaces[nPort]->objectDetection.createDetection();
            MyInterface::interfaces[nPort]->objectDetection.detection(QString("../").append(MyInterface::interfaces[nPort]->dirName));
        }
        YUVImage.~Mat();
        MyInterface::interfaces[nPort]->mutex.unlock();
    }
}

//实时视频码流数据获取 回调函数
void CALLBACK realDataCallBackEx(LLONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize,LONG param, LDWORD dwUser)
{
//    qDebug()<<"视频回调"<<lPlayHandle<<","<<dwDataType<<","<<dwBufSize;
    DahuaInterface* pIntf = (DahuaInterface*)dwUser;
    if (dwBufSize > 0 && pIntf->nPort != -1)
    {
        if (!PLAY_InputData(pIntf->nPort, pBuffer, dwBufSize))
        {
            qDebug()<<"fail input data:"<<pIntf->nPort;
        }
        else
        {
//            qDebug()<<"success input data:"<<pIntf->nPort;
        }

    }
}

QPixmap DahuaInterface::getPixmap(){
    if(isLogin){
        mutex.lock();
        int count = 0;
        while(this->imageStatus != 2 && count < 5)
        {
            count++;
            waitCondition.wait(&mutex,50);
        }
        if(this->imageStatus == 2){
            this->imageStatus = 3;
        }
        mutex.unlock();
        return pixmap;
    }
    else{
        return MyInterface::getPixmap();
    }
}

bool DahuaInterface::login(){
    NET_DEVICEINFO_Ex info_ex = { 0 };
    int err = 0;
    LONG lLoginID = CLIENT_LoginEx2(this->ip.toLatin1().data(), this->port, this->userName.toLatin1().data(), this->passwd.toLatin1().data(), EM_LOGIN_SPEC_CAP_TCP, NULL, &info_ex, &err);
    if(lLoginID == 0)
    {
        qDebug()<<"login error:"<<err<<",ip:"<<ip<<",port:"<<port<<",username:"<<userName<<",passwd:"<<passwd;
        return false;
    }
    this->loginId = lLoginID;

    qDebug()<<"login success"<<loginId<<","<<info_ex.nChanNum;
    //启动预览并设置回调数据流

    LLONG lRealPlay = CLIENT_RealPlayEx(lLoginID, 0, NULL, DH_RType_Realplay);
    if (0 == lRealPlay)
    {
        qDebug()<<"login error:CLIENT_RealPlayEx失败";
        return false;
    }

    if (!CLIENT_SetRealDataCallBackEx(lRealPlay, realDataCallBackEx, (LDWORD)this, 0x0f)){
        qDebug()<<"login error:注册回调函数失败";
        return false;
    }

    //获取播放库通道号
    this->nPort = this->currentIndex;
    bool ret = PLAY_OpenStream(this->nPort, 0, 0, 1024*900);
//    bool ret = PlayM4_GetPort(&this->nPort);
    if(!ret){
        qDebug()<<"login error:set stream open mode";
        return false;
    }else{
        MyInterface::interfaces[this->nPort] = this;
        qDebug()<<"获取播放通道号成功:port:"<<this->nPort<<",index:"<<this->currentIndex;
    }
    QString dirName1 =  QString("./image/port/%1").arg(nPort);
    QDir dir;
    if(!dir.exists(dirName1)){
        qDebug()<<"mkdir:"<<dir.mkdir(dirName1)<<",dirName:"<<dirName1;
    }

    //设置播放库回调函数
    ret = PLAY_SetDecCallBackEx(this->nPort, DecCBFun1, NULL);
    // 开启播放
    ret = PLAY_Play(this->nPort, NULL);
    if(!ret){
        qDebug()<<"login error:paly";
        return false;
    }

    this->isLogin = true;
    objectDetection.reconnect();
    QObject::connect(&objectDetection, SIGNAL(detectionFinish(QString, vector<ObjectItem>))
                     ,this, SLOT(onDetectionFinish(QString, vector<ObjectItem>)));
    imageStatus = 0;
    return true;
}
