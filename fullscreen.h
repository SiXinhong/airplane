#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QMainWindow>
#include <QThread>

#include "fullthread.h"

class FullScreen : public QMainWindow
{
    Q_OBJECT

private:
    int number;

public:
    explicit FullScreen(QWidget *parent = 0);
    ~FullScreen();
    void setNumber(int num);
    int getNumber();
    //1个fullthread
    FullThread ft;
signals:

public slots:

};

#endif // FULLSCREEN_H
