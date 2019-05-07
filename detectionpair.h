#ifndef DETECTIONPAIR_H
#define DETECTIONPAIR_H
#include "myinterface.h"

class MyInterface;
class DetectionPair
{
public:
    DetectionPair(MyInterface* inter,QString imageName);
    MyInterface *inter;
    QString imageName;
};

#endif // DETECTIONPAIR_H
