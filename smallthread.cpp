#include "smallthread.h"
#include "myinterface.h"

SmallThread::SmallThread()
{
}

void SmallThread::run(){

}

void SmallThread::setNumber(int num){
    this->number = num;
}

int SmallThread::getNumber(){
    return this->number;
}
