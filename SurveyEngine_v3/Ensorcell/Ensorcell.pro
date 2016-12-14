#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T19:18:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ensorcell
TEMPLATE = app

RC_FILE = myapp.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    splash.cpp \
    addquestiondialog.cpp \
    childwindow.cpp \
    elementdialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    splash.h \
    addquestiondialog.h \
    childwindow.h \
    elementdialog.h

RESOURCES += \
    res.qrc

DISTFILES +=
