TEMPLATE = subdirs

SUBDIRS += \
    VideoOutput \
    MediaPlayer \
    SubtitlesOutput \
    SubtitleParser

CONFIG += c++14
QMAKE_CXXFLAGS += -Werror -Wall

DISTFILES += \
    run_tests.sh
