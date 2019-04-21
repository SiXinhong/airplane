#ifndef CONFIGUTIL_H
#define CONFIGUTIL_H
#include <QString>


class ConfigUtil
{
public:
    ConfigUtil();
    static int isOpenCam[24];//是否打开摄像头，0不打开，1打开海康摄像头，2打开大华摄像头
    static QString ip[24];
    static QString user[24];
    static QString passwd[24];
    static int port[24];
    static void readConfigs();

    static bool isOpenDetect;

private:
    static void readCamConfigs();
    static void readOtherConfigs();
};

#endif // CONFIGUTIL_H
