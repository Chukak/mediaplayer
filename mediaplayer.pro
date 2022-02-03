TEMPLATE = app

QT += qml quick widgets multimedia core
CONFIG += c++14
QMAKE_CXXFLAGS += -Werror -Wall

SOURCES += \
    src/main.cpp \
    src/videooutput.cpp \
    src/mediaplayer.cpp \
    src/subtitleparser.cpp \
    src/subtitlesoutput.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/videooutput.h \
    src/mediaplayer.h \
    src/subtitleitem.h \
    src/subtitleparser.h \
    src/subtitlesoutput.h

DISTFILES += \
    .gitignore \
    build.sh \
    mediaplayer.png

TRANSLATIONS += \
    mediaplayer_ru_RU.ts

DEFINES += TRANSLATIONS_DIR=\\\"$$PWD\\\"
