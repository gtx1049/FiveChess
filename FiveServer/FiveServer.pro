#-------------------------------------------------
#
# Project created by QtCreator 2012-06-22T00:04:59
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = FiveServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    tcpsender.cpp \
    tcpreciever.cpp

HEADERS += \
    server.h \
    tcpsender.h \
    tcpreciever.h \
    const.h \
    message.h
