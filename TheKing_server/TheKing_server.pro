#-------------------------------------------------
#
# Project created by QtCreator 2019-08-22T15:57:03
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheKing_server
TEMPLATE = app


SOURCES += main.cpp\
    server.cpp \
    mysql.cpp \
    mythread.cpp

HEADERS  += \
    server.h \
    mysql.h \
    head.h \
    mythread.h

FORMS    += \
    server.ui

RESOURCES += \
    res.qrc
