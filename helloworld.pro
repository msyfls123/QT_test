#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T20:58:16
#
#-------------------------------------------------

QT       += core gui\
         webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helloworld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tray.cpp

HEADERS  += mainwindow.h \
    newspaper.h \
    reader.h \
    tray.h
QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    helloworld.qrc
