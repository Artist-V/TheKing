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
        mylog.cpp \
    myconnect.cpp \
    mainwindow.cpp \
    myreg.cpp \
    myanser.cpp \
    mypaper.cpp \
    mysingleanser.cpp

HEADERS  += mylog.h \
    myconnect.h \
    mainwindow.h \
    myreg.h \
    myanser.h \
    mypaper.h \
    mysingleanser.h \
    head.h

FORMS    += mylog.ui \
    mainwindow.ui \
    myreg.ui \
    myanser.ui \
    mypaper.ui \
    mysingleanser.ui

RESOURCES += \
    res.qrc
