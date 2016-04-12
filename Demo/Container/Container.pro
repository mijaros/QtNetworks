#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T21:54:32
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Container
TEMPLATE = lib

DEFINES += CONTAINER_LIBRARY

SOURCES += container.cpp

HEADERS += container.h\
        container_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
