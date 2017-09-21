QT += core gui
QT += widgets

CONFIG += c++11

TARGET = test_MovementComputer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include( ../common.pri)

SOURCES += \
    test_MovementComputer.cpp \
    ../../ItemList.cpp \
    ../../MovementComputer.cpp \

HEADERS  += ../../abstractitem.h \
        ../../ItemList.h \
        ../../MovementComputer.h \
