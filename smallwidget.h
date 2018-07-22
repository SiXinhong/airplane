#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>
#include <QThread>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QGridLayout>

#include <smallthread.h>
#include <fullscreen.h>

class SmallWidget : public QWidget
{
    Q_OBJECT

private:
    int number;

public:
    explicit SmallWidget(int index, QWidget *parent = 0);
    ~SmallWidget();
    QWidget *upWidget;
    QWidget *downWidget;
    QLabel *upLabel;
    QLabel *downLabel;
    QGridLayout *gridLayout;
    SmallThread *threadInterface;
    FullScreen upScreen;
    FullScreen downScreen;
    void resizeEvent(QResizeEvent *);
    void setNumber(int num);
    int getNumber();
    void showNext();

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
signals:

public slots:


};

#endif // SMALLWIDGET_H
