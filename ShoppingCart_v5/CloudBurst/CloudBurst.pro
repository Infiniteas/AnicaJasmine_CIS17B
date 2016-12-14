#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T18:19:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CloudBurst
TEMPLATE = app
RC_FILE = myapp.rc

SOURCES += main.cpp \
    mywindow.cpp \
    splash.cpp \
    logindialog.cpp

HEADERS  += \
    mywindow.h \
    splash.h \
    logindialog.h

RESOURCES += \
    src.qrc
