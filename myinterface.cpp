#include "myinterface.h"
#include <QTime>
#include <QDebug>
#include <QDir>

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

void MyInterface::setLogin(QString ip,QString userName,QString passwd,int port){
    this->ip = ip;
    this->userName = userName;
    this->passwd = passwd;
    this->port = port;
}

QPixmap MyInterface::getPixmap(){
    if(isLogin)
        return getPixmapFromRemote();
    else
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
