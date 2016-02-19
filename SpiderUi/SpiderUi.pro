#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T03:50:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpiderUi
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    DownloadView.cpp \
    Image.cpp \
    DownloadDispatcher.cpp \
    Downloader.cpp

HEADERS  += MainWindow.h \
    DownloadView.h \
    Image.h \
    DownloadDispatcher.h \
    Downloader.h

FORMS    += MainWindow.ui

INCLUDEPATH += $$PWD/../include
DESTDIR += $$PWD/../lib

CONFIG += debug_and_release

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../lib -lSpiderd
} else {
    LIBS += -L$$PWD/../lib -lSpider
}

RESOURCES += \
    res.qrc
