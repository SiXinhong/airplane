#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QMainWindow>
#include <QThread>
#include <QLabel>

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
    QLabel label;
    void resizeEvent(QResizeEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
signals:

public slots:

};

#endif // FULLSCREEN_H
