TEMPLATE = subdirs

SUBDIRS += \
    MediaPlayer \
    VideoOutput
CONFIG += c++14
QMAKE_CXXFLAGS += -Werror -Wall
