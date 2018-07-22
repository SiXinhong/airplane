#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>
#include <QThread>
#include <QPoint>
#include <QMouseEvent>

#include "myinterface.h"

class SmallWidget : public QWidget
{
    Q_OBJECT

private:
    int number;

public:
    explicit SmallWidget(QWidget *parent = 0);
    void setNumber(int num);
    int getNumber();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
signals:

public slots:


};

#endif // SMALLWIDGET_H
