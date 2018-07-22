#ifndef FULLTHREAD_H
#define FULLTHREAD_H

#include <QThread>

#include "myinterface.h"

class FullThread: public QThread
{

private:
    int number;
    bool isActive;

public:
    FullThread();
    void run();
    void setNumber(int num);
    int getNumber();
    void setActive(bool act);
    bool getActvie();
};

#endif // FULLTHREAD_H
