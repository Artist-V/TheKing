#-------------------------------------------------
#
# Project created by QtCreator 2019-08-22T16:04:08
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheKing_client
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    myanser.cpp \
    mypaper.cpp \
    mysingleanser.cpp \
    mythread.cpp \
    logwidget.cpp \
    myjudge.cpp

HEADERS  += \
    mainwindow.h \
    myanser.h \
    mypaper.h \
    mysingleanser.h \
    head.h \
    mythread.h \
    logwidget.h \
    myjudge.h

FORMS    += \
    mainwindow.ui \
    myanser.ui \
    mypaper.ui \
    mysingleanser.ui \
    logwidget.ui

RESOURCES += \
    res.qrc
