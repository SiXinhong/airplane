#ifndef BOTTOMLABEL_H
#define BOTTOMLABEL_H
#include<QLabel>
#include<QTimer>

class BottomLabel:public QLabel
{
    Q_OBJECT
public:
    BottomLabel(QWidget *);

    static bool is_draw;

    QTimer *timer;

    void paintEvent(QPaintEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void mouseDoubleClickEvent(QMouseEvent *e);

public slots:
    void slotClicked();
};

#endif // BOTTOMLABEL_H
