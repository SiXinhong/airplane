#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>
#include "DbgHelp.h"
#include <QDebug>

static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    return EXCEPTION_EXECUTE_HANDLER;
}
int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("XX机场鸟情智能视频监控报警系统");
    w.show();

    return a.exec();
}
