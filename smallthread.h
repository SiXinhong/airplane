#ifndef SMALLTHREAD_H
#define SMALLTHREAD_H

#include <QThread>

#include "myinterface.h"

class SmallThread: public QThread
{

private:
    int number;

public:
    SmallThread();
    void run();
    void setNumber(int num);
    int getNumber();
};

#endif // SMALLTHREAD_H
