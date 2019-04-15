#include "objectdetection.h"

ObjectDetection::ObjectDetection(QObject *parent):QObject(parent)
{
//    client = new QTcpSocket(this);
//    /*------- 连接信号与槽 -------*/
//    /* 一连上 server 就发信息 */
//    connect(client, SIGNAL(connected()),
//       this, SLOT(send_msg()));
////    connect(client,SIGNAL(disconnected()),this,SLOT(disConnect()));
//    /* server 有回复就读取 */
//    connect(client, SIGNAL(readyRead()),
//       this, SLOT(read_msg()));
//    /* server 把连接断了就发出提示 */
//    connect(client, SIGNAL(disconnected()),
//       this, SLOT(end_connent()));
//       /* 向 server 发送连接请求 */
//    client->connectToHost(QHostAddress::LocalHost, 9999);
//    bool f = client->waitForConnected(200);
//    if(f==false){
//        this->runScript();
//    }
}

void ObjectDetection::createDetection()
{
    client->write("setDetection");
    client->flush();
}

void ObjectDetection::detection(QString filename)
{
    client->write(filename.toLatin1());
    client->flush();
}

void ObjectDetection::reconnect()
{
    client = new QTcpSocket(this);
    /*------- 连接信号与槽 -------*/
    /* 一连上 server 就发信息 */
    connect(client, SIGNAL(connected()),
       this, SLOT(send_msg()));
//    connect(client,SIGNAL(disconnected()),this,SLOT(disConnect()));
    /* server 有回复就读取 */
    connect(client, SIGNAL(readyRead()),
       this, SLOT(read_msg()));
    /* server 把连接断了就发出提示 */
    connect(client, SIGNAL(disconnected()),
       this, SLOT(end_connent()));
       /* 向 server 发送连接请求 */
    client->connectToHost(QHostAddress::LocalHost, 9999);
    bool f = client->waitForConnected(200);
    if(f==false){
        this->runScript();
    }else{
        qDebug()<<"connect success";
    }
}

void ObjectDetection::runScript()
{
    QProcess *p =new QProcess();
    p->start("f:/ai/python36/python",QStringList()<<"./detect/MySocket.py");
    qDebug()<<"run objectDetection";
    bool f=false;
    while(!f){
        client->connectToHost(QHostAddress::LocalHost, 9999);
        f = client->waitForConnected(2000);
        qDebug()<<"connect to objectDetection:"<<f;
    }

}

void ObjectDetection::send_msg()
{

}

void ObjectDetection::read_msg()
{
    QByteArray ba = client->readAll();
    QString s(ba);
    if(s == "Detection"){
        emit createDetectionFinish();
//        detection("t.jpg");

    }else{
        ImageObjects objects;
        objects.LoadJson(s);
        emit detectionFinish(objects.filename,objects.om);
    }
    qDebug()<<s;
}

void ObjectDetection::end_connent()
{
    qDebug()<<"connect end";
//    this->runScript();
}

void ObjectDetection::disConnect()
{

}
