#include "configutil.h"
#include <QSettings>

ConfigUtil::ConfigUtil()
{

}

int ConfigUtil::isOpenCam[24];
QString ConfigUtil::ip[24];
QString ConfigUtil::user[24];
QString ConfigUtil::passwd[24];
int ConfigUtil::port[24];
bool ConfigUtil::isOpenDetect = false;
bool ConfigUtil::isOpenDetectLocal = false;

void ConfigUtil::readConfigs(){
    ConfigUtil::readCamConfigs();
    ConfigUtil::readOtherConfigs();
}

void ConfigUtil::readCamConfigs(){
    /* 摄像头部分分三节，第一节switch，表示是否启用摄像头用哪个摄像头，
     * 路径是switch/interface1=xx，xx为hk启用海康威视摄像头，为dh启用大华，其他的不启用摄像头
     * 第二节hkconfig配置海康威视的ip，用户名、密码、端口等
     * 第三节dhconfig配置大华的ip，用户名、密码、端口等
    */
    QString iniFilePath = "./config/camConfig.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    for(int i=0;i<24;i++){
        QString switchconfig = settings.value(QString("switch/interface%1").arg(i)).toString();
        if(switchconfig == QString("hk")){
            ConfigUtil::isOpenCam[i] = 1;
            ConfigUtil::ip[i] = settings.value(QString("hkconfig/ip%1").arg(i)).toString();
            ConfigUtil::user[i] = settings.value(QString("hkconfig/user%1").arg(i)).toString();
            ConfigUtil::passwd[i] = settings.value(QString("hkconfig/passwd%1").arg(i)).toString();
            ConfigUtil::port[i] = settings.value(QString("hkconfig/port%1").arg(i)).toInt();
        }else if(switchconfig == QString("dh")){
            ConfigUtil::isOpenCam[i] = 2;
            ConfigUtil::ip[i] = settings.value(QString("dhconfig/ip%1").arg(i)).toString();
            ConfigUtil::user[i] = settings.value(QString("dhconfig/user%1").arg(i)).toString();
            ConfigUtil::passwd[i] = settings.value(QString("dhconfig/passwd%1").arg(i)).toString();
            ConfigUtil::port[i] = settings.value(QString("dhconfig/port%1").arg(i)).toInt();
        }else{
            ConfigUtil::isOpenCam[i] = 0;
        }
    }
}

void ConfigUtil::readOtherConfigs(){
    QString iniFilePath = "./config/commonConfig.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    ConfigUtil::isOpenDetect = settings.value(QString("common/openDetect")).toBool();

    ConfigUtil::isOpenDetectLocal = settings.value(QString("common/openDetectLocal")).toBool();
}
