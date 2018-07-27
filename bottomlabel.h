#ifndef BOTTOMLABEL_H
#define BOTTOMLABEL_H
#include<QLabel>
#include<QTimer>

#include "smallwidget.h"

class BottomLabel:public QLabel
{
    Q_OBJECT
public:
    BottomLabel(QWidget *);

    ~BottomLabel();
    static bool is_draw;

    // *timer;

    void paintEvent(QPaintEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void mouseDoubleClickEvent(QMouseEvent *e);

public slots:
    //void slotClicked();
};

#endif // BOTTOMLABEL_H
