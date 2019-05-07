#include "detectionpair.h"

DetectionPair::DetectionPair(MyInterface* inter,QString imageName)
{
    this->inter = inter;
    this->imageName = imageName;
}
