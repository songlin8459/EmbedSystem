#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T22:11:22
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Myclient
TEMPLATE = app


SOURCES += main.cpp\
    ipwindow.cpp \
    mythread.cpp \
    mainwindow.cpp

HEADERS  += \
    ipwindow.h \
    mainwindow.h \
    mythread.h

FORMS    += \
    ipwindow.ui \
    mainwindow.ui


RC_ICONS +=video.ico
