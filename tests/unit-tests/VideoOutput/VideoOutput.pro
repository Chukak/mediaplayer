#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T18:48:04
#
#-------------------------------------------------

QT += testlib quick multimedia

QT -= gui

TARGET = tst_videooutputtest
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../../src/videooutput.cpp \
        ../../../src/mediaplayer.cpp \
        tst_videooutputtest.cpp 

HEADERS += \
        ../../../src/videooutput.h \
        ../../../src/mediaplayer.h \

DEFINES += SRCDIR=\\\"$$PWD/\\\"
