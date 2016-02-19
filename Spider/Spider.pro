QT += core network
QT -= gui

TARGET = Spider
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = lib
DEFINES += SPIDER_LIBRARY

SOURCES += main.cpp \
    AbstractSpider.cpp \
    AbstractParser.cpp \
    Parser.cpp \
    DataQueue.cpp \
    Fetcher.cpp \
    Spider.cpp

HEADERS += \
    AbstractSpider.h \
    AbstractParser.h \
    Parser.h \
    DataQueue.h \
    global.h \
    Fetcher.h \
    Spider.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    TARGET = Spiderd
} else {
    TARGET = Spider
}
DESTDIR += ../lib

win32
{
    SRC_DIR = $$PWD\*.h
    SRC_DIR ~= s,/,\\,g

    DST_DIR = $$PWD\..\include
    DST_DIR ~= s,/,\\,g

    QMAKE_POST_LINK += xcopy $$SRC_DIR  $$DST_DIR  /y /s
}

