QT += core
QT -= gui

CONFIG += c++11

TARGET = WebSocket
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    socketutil.cpp \
    clienthandler.cpp \
    webserver.cpp \
    comunicationcenter.cpp

HEADERS += \
    socketutil.h \
    clienthandler.h \
    webserver.h \
    comunicationcenter.h
