#include "fullthread.h"
#include "myinterface.h"


FullThread::FullThread()
{
}

void FullThread::run(){

}

void FullThread::setNumber(int num){
    this->number = num;
}

int FullThread::getNumber(){
    return this->number;
}

void FullThread::setActive(bool act){
    this->isActive = act;
}

bool FullThread::getActvie(){
    return this->isActive;
}
