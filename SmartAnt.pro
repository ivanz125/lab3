#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T12:36:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartAnt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    state.cpp \
    transit.cpp \
    behavior.cpp \
    ant.cpp \
    gamefield.cpp \
    cell.cpp \
    fieldgenerator.cpp \
    behaviorgenerator.cpp

HEADERS  += mainwindow.h \
    Action.h \
    state.h \
    transit.h \
    behavior.h \
    Direction.h \
    ant.h \
    gamefield.h \
    cell.h \
    fieldgenerator.h \
    behaviorgenerator.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
