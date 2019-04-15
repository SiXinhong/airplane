#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H
#include<QtNetwork/QtNetwork>
#include<QProcess>
#include"imageobjects.h"

class ObjectDetection: public QObject
{
    Q_OBJECT
public:
    ObjectDetection(QObject *parent=0);
    QTcpSocket *client;
    bool flag;
    //初始化目标检测模型
    void createDetection();
    //检测 参数为文件名
    void detection(QString filename);
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
    //检测完毕，返回值为文件名和检测到的各种目标
    void detectionFinish(QString filename, vector<ObjectItem>);
};

#endif // OBJECTDETECTION_H
