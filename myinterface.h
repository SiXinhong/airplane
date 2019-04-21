#ifndef MYINTERFACE_H
#define MYINTERFACE_H
#include <QPixmap>
#include <QVector>
#include <Windows.h>
#include "objectdetection.h"
#include "configutil.h"

class MyInterface :  public QObject
{
    Q_OBJECT
public:
    MyInterface(int start);
    MyInterface(int start,QString ip,QString userName,QString passwd,int port);
    void setLogin(QString ip,QString userName,QString passwd,int port);
    virtual QPixmap getPixmap();
    virtual bool login() = 0;
    bool isLogin;//是否已经登录
    QString ip;
    QString userName;
    QString passwd;
    int port;
    LONG loginId;//登录后返回的登录标识，后续调用都使用这个
    int currentIndex;
    QVector<QPixmap> cache;
    QString dirName;
    LONG nPort;//播放库通道号
    QPixmap pixmap;
    ObjectDetection objectDetection;
    QMutex mutex;
    QWaitCondition waitCondition;
    int imageStatus;// -1:初始化，不做任何动作0：无图片文件，1：正在被检测，2：检测成功，已存入this.pixmap，3：已读取过this.pixmap
    static MyInterface *interfaces[24];
    void setPixMap(QPixmap pixmap);

public slots:
    void onDetectionFinish(QString filename, vector<ObjectItem>);
};

#endif // MYINTERFACE_H
