QT += testlib multimedia

QT -= gui

TARGET = tst_mediaplayertest
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase
QMAKE_CXXFLAGS += -Werror -Wall

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../../src/subtitleparser.cpp \
        ../../../src/subtitlesoutput.cpp \
        ../../../src/mediaplayer.cpp \
        tst_mediaplayertest.cpp 

HEADERS += \
        ../../../src/subtitleitem.h \
        ../../../src/subtitleparser.h \
        ../../../src/subtitlesoutput.h \
        ../../../src/mediaplayer.h
