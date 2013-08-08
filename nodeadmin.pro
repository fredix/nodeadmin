#-------------------------------------------------
#
# Project created by QtCreator 2013-06-28T14:15:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nodeadmin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nodecast_api.cpp \
    nodes.cpp

HEADERS  += mainwindow.h \
    nodecast_api.h \
    nodes.h

FORMS    += mainwindow.ui \
    nodes.ui
