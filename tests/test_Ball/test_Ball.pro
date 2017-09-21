QT += core gui
QT += widgets

CONFIG += c++11

TARGET = test_Ball
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include( ../common.pri)

SOURCES += \
    test_Ball.cpp \
    ../../Ball.cpp \
    ../../ItemList.cpp \

HEADERS  += ../../abstractitem.h \
        ../../ItemList.h \
        ../../Ball.h
