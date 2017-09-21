QT += core gui
QT += widgets

CONFIG += c++11

TARGET = test_BallsList
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include( ../common.pri)

SOURCES += \
    test_ItemList.cpp \
    ../../ItemList.cpp \

HEADERS  += ../../abstractitem.h \
        ../../ItemList.h \


