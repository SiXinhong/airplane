#ifndef MYINTERFACE_H
#define MYINTERFACE_H
#include <QPixmap>

class MyInterface
{
public:
    MyInterface(int start);
    QPixmap getPixmap();
    int currentIndex;
};

#endif // MYINTERFACE_H
