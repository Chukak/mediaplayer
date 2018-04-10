#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T18:52:03
#
#-------------------------------------------------

QT += testlib multimedia

QT -= gui

TARGET = tst_mediaplayertest
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../../src/mediaplayer.cpp \
        tst_mediaplayertest.cpp 

HEADERS += \
        ../../../src/mediaplayer.h \

DEFINES += SRCDIR=\\\"$$PWD/\\\"
