#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("XX机场鸟情智能视频监控报警系统");
    w.show();

    return a.exec();
}
