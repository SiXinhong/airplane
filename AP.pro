#-------------------------------------------------
#
# Project created by QtCreator 2018-07-14T15:30:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AP
TEMPLATE = app

INCLUDEPATH += .\install\include
INCLUDEPATH += .\install\include\opencv

INCLUDEPATH += .\hcnet\include
INCLUDEPATH += .\dahua\include
LIBS += -L .\install\x64\mingw\lib\libopencv_*.a\
            .\hcnet\lib\HC*.lib\
            .\hcnet\lib\PlayCtrl.lib\
            .\dahua\lib\dh*.lib\
            .\dahua\lib\dhplay.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    myinterface.cpp \
    smallwidget.cpp \
    fullscreen.cpp \
    cvutil.cpp \
    smallthread.cpp \
    fullthread.cpp \
    bottomlabel.cpp \
    imageobjects.cpp \
    objectdetection.cpp \
    objectitem.cpp \
    dahuainterface.cpp \
    configutil.cpp \
    hkinterface.cpp

HEADERS  += mainwindow.h \
    myinterface.h \
    smallwidget.h \
    fullscreen.h \
    cvutil.h \
    smallthread.h \
    fullthread.h \
    bottomlabel.h \
    PlayM4.h \
    imageobjects.h \
    objectdetection.h \
    objectitem.h \
    dahuainterface.h \
    PlayApi.h \
    configutil.h \
    hkinterface.h

FORMS    += mainwindow.ui
