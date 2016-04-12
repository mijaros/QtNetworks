QT += core
QT -= gui
QT += network

CONFIG += c++11

TARGET = Client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Container/release/ -lContainer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Container/debug/ -lContainer
else:unix: LIBS += -L$$OUT_PWD/../Container/ -lContainer

INCLUDEPATH += $$PWD/../Container
DEPENDPATH += $$PWD/../Container
