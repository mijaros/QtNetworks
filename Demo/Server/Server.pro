QT += core
QT -= gui

CONFIG += c++11

TARGET = Server
CONFIG += console
QT += network
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    socketthread.cpp

HEADERS += \
    server.h \
    socketthread.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Container/release/ -lContainer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Container/debug/ -lContainer
else:unix: LIBS += -L$$OUT_PWD/../Container/ -lContainer

INCLUDEPATH += $$PWD/../Container
DEPENDPATH += $$PWD/../Container
