#ifndef MYINTERFACE_H
#define MYINTERFACE_H
#include <QPixmap>
#include <QVector>
#include <Windows.h>
#include <HCNetSDK.h>
#include "objectdetection.h"

class MyInterface :  public QObject
{
    Q_OBJECT
public:
    MyInterface(int start);
    MyInterface(int start,QString ip,QString userName,QString passwd,int port);
    void setLogin(QString ip,QString userName,QString passwd,int port);
    QPixmap getPixmap();
    QPixmap getPixmapFromRemote();
    bool login();
    bool isLogin;//是否已经登录
    QString ip;
    QString userName;
    QString passwd;
    int port;
    LONG loginId;//登录后返回的登录标识，后续调用都使用这个
    int deviceChanNum;//设备的通道数
    int	startChan;//设备开始通道号
    int iPChanNum;//最大数字通道个数
    int iPStartChan;//数字通道起始通道号
    LPNET_DVR_JPEGPARA JpegPara;//获取图片时的参数，图片质量
    int currentIndex;
    QVector<QPixmap> cache;
    QString dirName;
    LONG nPort;//播放库通道号
    QPixmap pixmap;
    ObjectDetection objectDetection;
    QMutex mutex;
    QWaitCondition waitCondition;
    int imageStatus;// -1:初始化，不做任何动作0：无图片文件，1：正在被检测，2：检测成功，已存入this.pixmap，3：已读取过this.pixmap
    bool isOpenDetectSwitch;// 是否开启检测目标的开关，true:打开检测,false:关闭检测

public slots:
    void onDetectionFinish(QString filename, vector<ObjectItem>);
};

#endif // MYINTERFACE_H
