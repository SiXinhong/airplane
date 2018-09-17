#ifndef MYINTERFACE_H
#define MYINTERFACE_H
#include <QPixmap>
#include <QVector>

class MyInterface
{
public:
    MyInterface(int start);
    QPixmap getPixmap();
    int currentIndex;
    QVector<QPixmap> cache;
};

#endif // MYINTERFACE_H
