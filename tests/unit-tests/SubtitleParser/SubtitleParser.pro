QT       += testlib

QT       -= gui

TARGET = tst_subtitleparsertest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += testcase
QMAKE_CXXFLAGS += -Werror -Wall

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        ../../../src/subtitleparser.cpp \
        tst_subtitleparsertest.cpp

HEADERS += \
        ../../../src/subtitleitem.h \
        ../../../src/subtitleparser.h
