#include "myinterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>
#include "PlayM4.h"
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

LONG nPort;//播放库通道号
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
        qDebug()<< "the frame infomation is T_YV12";
        cv::Mat g_BGRImage;
        g_BGRImage.create(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
        cv::Mat YUVImage(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, (unsigned char*)pBuf);

        cv::cvtColor(YUVImage, g_BGRImage, cv::COLOR_YUV2BGR_YV12);
        QString dir =  QString("./image/5/tmp.jpg");
        cv::imwrite(dir.toStdString(),g_BGRImage);
        qDebug()<< "write image to "<<dir;
        YUVImage.~Mat();
    }
}

//实时视频码流数据获取 回调函数
void CALLBACK g_RealDataCallBack_V30(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void* pUser)
{
    if (dwDataType == NET_DVR_STREAMDATA)//码流数据
    {
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                qDebug()<<"fail input data:"<<nPort;
            }
            else
            {
                qDebug()<<"success input data:"<<nPort;
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
    return QPixmap(QString("./image/5/tmp.jpg"));
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+currentIndex);
//    currentIndex = (currentIndex+qrand()%10)%50;
//    //return QPixmap(QString("./image/%1.jpg").arg(currentIndex));
//    return cache.at(currentIndex);
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
    bool ret = PlayM4_GetPort(&nPort);
    if(!ret){
        qDebug()<<"login error:set stream open mode";
        return false;
    }else{
        qDebug()<<"获取播放通道号成功:port:"<<nPort<<",index:"<<this->currentIndex;
    }

    //设置流模式
    ret = PlayM4_SetStreamOpenMode(nPort, STREAME_REALTIME);
    if(!ret){
        qDebug()<<"login error:fail to get port";
        return false;
    }
    //打开流
    ret = PlayM4_OpenStream(nPort, NULL, 0, 1024 * 1024);
    if(!ret){
        qDebug()<<"login error:OpenStream";
        return false;
    }
    //设置播放库回调函数
    ret = PlayM4_SetDecCallBackExMend(nPort, DecCBFun, NULL, 0, NULL);
    // 开启播放
    ret = PlayM4_Play(nPort, NULL);
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

    if (!NET_DVR_RealPlay_V40(this->loginId, &struPlayInfo, g_RealDataCallBack_V30, NULL))
    {
        qDebug()<<"login error:注册回调函数失败" + NET_DVR_GetLastError();
        return false;
    }

    this->isLogin = true;
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
