#-------------------------------------------------
#
# Project created by QtCreator 2016-07-09T18:40:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = solarsystem
TEMPLATE = app

LIBS += -L../../lib
LIBS += -lnbodysim

INCLUDEPATH += ../../src/
DEPENDPATH += $$INCLUDEPATH
VPATH += $$INCLUDEPATH

QMAKE_CXXFLAGS += -std=c++11

CONFIG += silent

SOURCES += \
  main.cpp \
  mainwindow.cpp \
  solarsystemscene.cpp \
  bodyitem.cpp

HEADERS  += \
  mainwindow.h \
  solarsystemscene.h \
  bodyitem.h
