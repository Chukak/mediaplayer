TEMPLATE = app

QT += qml quick widgets multimedia

SOURCES += main.cpp \
    src/videooutput.cpp \
    src/mediaplayer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/videooutput.h \
    src/mediaplayer.h

