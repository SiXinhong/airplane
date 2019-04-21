#ifndef DAHUAINTERFACE_H
#define DAHUAINTERFACE_H
#include "dhnetsdk.h"
#include "myinterface.h"

class DahuaInterface : public MyInterface
{
    Q_OBJECT
public:
    DahuaInterface(int start);
    DahuaInterface(int start,QString ip,QString userName,QString passwd,int port);
    QPixmap getPixmap();
    bool login();
};

#endif // DAHUAINTERFACE_H
