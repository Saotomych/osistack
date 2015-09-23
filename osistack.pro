#-------------------------------------------------
#
# Project created by QtCreator 2015-09-23T17:47:31
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = osistack
TEMPLATE = lib
CONFIG += staticlib

SOURCES += osistack.cpp

HEADERS += osistack.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
