QT += core
QT -= gui

CONFIG += c++11

TARGET = ReviewAssignment_1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Table.cpp \
    TableInherited.cpp

HEADERS += \
    Table.h \
    TableInherited.h
