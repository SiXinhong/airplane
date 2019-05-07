#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H
#include<QtNetwork/QtNetwork>
#include<QProcess>
#include"imageobjects.h"
#include "detectionpair.h"
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "detectionpair.h"

class DetectionPair;
class ObjectDetection: public QThread
{
    Q_OBJECT
public:
    static ObjectDetection* getInstance();
    void run();
    QTcpSocket *client;
    bool initFlag;// 初始化标记，createDetection且回调后置为true
    //初始化目标检测模型
    void createDetection();
    //检测 参数为文件名
    void detection(DetectionPair pair);
    void reconnect();
    void runScript();
public slots:
    void send_msg(); // 向server发信息
    void read_msg(); // 读server回复的信息
    void end_connent(); // 被断开连接后提示
    void disConnect();
signals:
    //目标检测模型初始化完毕
    void createDetectionFinish();
private:
    ObjectDetection();// 单例，不允许显式创建实例
    static ObjectDetection *instance;
    QQueue<DetectionPair> detectQueue;
    //检测 参数为文件名
    void detection(QString fileName);
    QMutex mutex;
    QWaitCondition waitCond;
    bool isProcessing;// 是否正在处理检测
};

#endif // OBJECTDETECTION_H
