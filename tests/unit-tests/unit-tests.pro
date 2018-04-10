TEMPLATE = subdirs

SUBDIRS += \
    VideoOutput \
    MediaPlayer

CONFIG += c++14
QMAKE_CXXFLAGS += -Werror -Wall
