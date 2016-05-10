#-------------------------------------------------
#
# Project created by QtCreator 2014-09-03T14:32:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = powsimu
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../powot_simulator/release/ -lpowot_simulator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../powot_simulator/debug/ -lpowot_simulator
else:unix: LIBS += -L$$OUT_PWD/../powot_simulator/ -lpowot_simulator

INCLUDEPATH += $$PWD/../powot_simulator
DEPENDPATH += $$PWD/../powot_simulator
