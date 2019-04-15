#include "myinterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>
#include "PlayM4.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "cvutil.h"
#include <QPainter>

MyInterface* interfaces[24];

MyInterface::MyInterface(int start)
{
    currentIndex = start;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }
    this->JpegPara = new NET_DVR_JPEGPARA;
    this->JpegPara->wPicSize = 9;//9-HD1080P(1920*1080)
    this->JpegPara->wPicQuality = 0;//wPicQuality 图片质量系数：0-最好，1-较好，2-一般
    this->isLogin = false;
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    QDir dir;
    this->dirName = QString("./image/%1").arg(this->currentIndex);
    if(!dir.exists(dirName)){
        qDebug()<<"mkdir:"<<dir.mkdir(dirName)<<",dirName:"<<dirName;
    }
    dirName = dirName.append("/tmp.jpg");

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);

    this->isOpenDetectSwitch = true;
    this->imageStatus = -1;
}

MyInterface::MyInterface(int start,QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
    currentIndex = start;
    for(int i=0;i<50;i++){
        cache.append(QPixmap(QString("./image/%1.jpg").arg(i)));
    }
    this->JpegPara = new NET_DVR_JPEGPARA;
    this->JpegPara->wPicSize = 9;//9-HD1080P(1920*1080)
    this->JpegPara->wPicQuality = 0;//wPicQuality 图片质量系数：0-最好，1-较好，2-一般
    this->isLogin = false;
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
}

//数据解码回调函数，
//功能：将YV_12格式的视频数据流转码为可供opencv处理的BGR类型的图片数据
void CALLBACK DecCBFun(long nPort, char* pBuf, long nSize, FRAME_INFO* pFrameInfo, long nUser, long nReserved2)
{
    if (pFrameInfo->nType == T_YV12)
    {
        interfaces[nPort]->mutex.lock();
        // 正在被检测
        if(interfaces[nPort]->imageStatus == 1 || interfaces[nPort]->imageStatus == -1){
            interfaces[nPort]->mutex.unlock();
            return;
        }
        qDebug()<<"DecCBFun"<<interfaces[nPort]->imageStatus;
        //qDebug()<< "the frame infomation is T_YV12";
        cv::Mat g_BGRImage;
        g_BGRImage.create(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
        cv::Mat YUVImage(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, (unsigned char*)pBuf);

        cv::cvtColor(YUVImage, g_BGRImage, cv::COLOR_YUV2BGR_YV12);
        //QString dir =  QString("./image/port/%1").arg(nPort).append("/tmp.jpg");
        //cv::imwrite(dir.toStdString(),g_BGRImage);
        //qDebug()<< "write image to "<<dir;
        if(!interfaces[nPort]->isOpenDetectSwitch){
            interfaces[nPort]->pixmap = CVUtil::cvMatToQPixmap(g_BGRImage);
        }else{
            cv::imwrite(interfaces[nPort]->dirName.toStdString(),g_BGRImage);
            //qDebug()<< "write image to "<<interfaces[nPort]->dirName;
            interfaces[nPort]->imageStatus = 1;// 设置为正在被检测
            interfaces[nPort]->objectDetection.createDetection();
            interfaces[nPort]->objectDetection.detection(QString("../").append(interfaces[nPort]->dirName));
        }
        YUVImage.~Mat();
        interfaces[nPort]->mutex.unlock();
    }
}

//实时视频码流数据获取 回调函数
void CALLBACK g_RealDataCallBack_V30(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser)
{
    if (dwDataType == NET_DVR_STREAMDATA)//码流数据
    {
        MyInterface* pIntf = (MyInterface*)pUser;
        if (dwBufSize > 0 && pIntf->nPort != -1)
        {
            if (!PlayM4_InputData(pIntf->nPort, pBuffer, dwBufSize))
            {
                qDebug()<<"fail input data:"<<pIntf->nPort;
            }
            else
            {
                //qDebug()<<"success input data:"<<pIntf->nPort;
            }

        }
    }
}

void MyInterface::setLogin(QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
}

QPixmap MyInterface::getPixmap(){
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
        //return QPixmap(QString("./image/port/%1").arg(nPort).append("/tmp.jpg"));
        //return getPixmapFromRemote();
    }
    else{
        currentIndex = (currentIndex+qrand()%10)%50;
        //return QPixmap(QString("./image/%1.jpg").arg(currentIndex));
        return cache.at(currentIndex);
    }
}

bool MyInterface::login(){
    NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
    memset(&DeviceInfoTmp,0,sizeof(NET_DVR_DEVICEINFO_V30));

    LONG lLoginID = NET_DVR_Login_V30(this->ip.toLatin1().data(),this->port,this->userName.toLatin1().data(),this->passwd.toLatin1().data(),&DeviceInfoTmp);
    if(lLoginID == -1)
    {
        qDebug()<<"login error:"<<NET_DVR_GetLastError()<<",ip:"<<ip<<",port:"<<port<<",username:"<<userName<<",passwd:"<<passwd;
        return false;
    }
    this->loginId = lLoginID;
    this->deviceChanNum = DeviceInfoTmp.byChanNum;
    this->iPChanNum = DeviceInfoTmp.byIPChanNum;
    this->startChan  = DeviceInfoTmp.byStartChan;
    this->iPStartChan  = DeviceInfoTmp.byStartDChan;





    //获取播放库通道号
    bool ret = PlayM4_GetPort(&this->nPort);
    if(!ret){
        qDebug()<<"login error:set stream open mode";
        return false;
    }else{
        interfaces[this->nPort] = this;
        qDebug()<<"获取播放通道号成功:port:"<<this->nPort<<",index:"<<this->currentIndex;
    }
    QString dirName1 =  QString("./image/port/%1").arg(nPort);
    QDir dir;
    if(!dir.exists(dirName1)){
        qDebug()<<"mkdir:"<<dir.mkdir(dirName1)<<",dirName:"<<dirName1;
    }
    //设置流模式
    ret = PlayM4_SetStreamOpenMode(this->nPort, STREAME_REALTIME);
    if(!ret){
        qDebug()<<"login error:fail to get port";
        return false;
    }
    //打开流
    ret = PlayM4_OpenStream(this->nPort, NULL, 0, 1024 * 1024);
    if(!ret){
        qDebug()<<"login error:OpenStream";
        return false;
    }
    //设置播放库回调函数
    ret = PlayM4_SetDecCallBackExMend(this->nPort, DecCBFun, NULL, 0, NULL);
    // 开启播放
    ret = PlayM4_Play(this->nPort, NULL);
    if(!ret){
        qDebug()<<"login error:paly";
        return false;
    }
    //启动预览并设置回调数据流
    NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
    struPlayInfo.hPlayWnd = NULL; //窗口为空，设备SDK不解码只取流
    struPlayInfo.lChannel = 1; //Channel number 设备通道
    struPlayInfo.dwStreamType = 0;// 码流类型，0-主码流，1-子码流，2-码流3，3-码流4, 4-码流5,5-码流6,7-码流7,8-码流8,9-码流9,10-码流10
    struPlayInfo.dwLinkMode = 0;// 0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-RTP/RTSP,5-RSTP/HTTP
    struPlayInfo.bBlocked = 1; //0-非阻塞取流, 1-阻塞取流, 如果阻塞SDK内部connect失败将会有5s的超时才能够返回,不适合于轮询取流操作.

    if (-1==NET_DVR_RealPlay_V40(this->loginId, &struPlayInfo, g_RealDataCallBack_V30, this))
    {
        qDebug()<<"login error:注册回调函数失败" << NET_DVR_GetLastError();
        return false;
    }

    this->isLogin = true;
    objectDetection.reconnect();
    QObject::connect(&objectDetection, SIGNAL(detectionFinish(QString, vector<ObjectItem>))
                     ,this, SLOT(onDetectionFinish(QString, vector<ObjectItem>)));
    imageStatus = 0;
    return true;
}

QPixmap MyInterface::getPixmapFromRemote(){
    if(!isLogin)
        return QPixmap();
    QTime t = QTime::currentTime();
    t.start();
    bool capture = false;
    // 调用失败重试几次
    for(int i=0;capture && i<5;i++){
        capture = NET_DVR_CaptureJPEGPicture(this->loginId,1,this->JpegPara,this->dirName.toLatin1().data());
        if(!capture){
            qDebug()<<"getPixmapFromRemote error:"<<NET_DVR_GetLastError();
        }
    }

    if(capture){
        return QPixmap(this->dirName);
    }else{
        return QPixmap();
    }
    qDebug()<<"getPixmapFromRemote:"<<t.toString("hh:mm:ss.zzz")<<"elapsed:"<<t.elapsed();
}

void MyInterface::onDetectionFinish(QString filename, vector<ObjectItem> items){
    qDebug()<<"onDetectionFinish";
    mutex.lock();
    this->pixmap = QPixmap(this->dirName);
    if(items.empty()){
        qDebug()<<"onDetectionFinish1";
        this->imageStatus = 2;
        mutex.unlock();
        return;
    }
    int count = items.size();
    QPainter painter(&pixmap);
    for (int i = 0; i < count; i++){
//        qDebug()<<"filename:"<<filename<<","<<items[i].name;
        painter.drawRect(QRect(items[i].startPoint,items[i].endPoint));
    }
    this->imageStatus = 2;
    waitCondition.wakeAll();
    mutex.unlock();
    qDebug()<<"onDetectionFinish2";

}
