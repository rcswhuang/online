#-------------------------------------------------
#
# Project created by huangw 2018-04-16T16:02:27
#
#-------------------------------------------------

QT       += core gui
QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = online
TEMPLATE = app

INCLUDEPATH += \
             ../include \
             ../include/H5IconGui \
             ../include/H5IconHelp \

SOURCES += main.cpp\
    honlineview.cpp \
    hpreviewwindow.cpp \
    #htemplatewindow.cpp \
    #hwfsystemtview.cpp \
    #htemplateview.cpp \
    hwfsystemwindow.cpp \
    honlinewindow.cpp \
    hwfsystemdoc.cpp \
    hwfsystemmgr.cpp \
    honlinescene.cpp \
    honlinetreewidget.cpp \
    hoperorderview.cpp \
    honlinerefreshthread.cpp \
    hkerneltest.cpp \
    hupdatethread.cpp

HEADERS  += \
    honlineview.h \
    #htemplatewindow.h \
    #hwfsystemtview.h \
    #htemplateview.h \
    hwfsystemwindow.h \
    honlinewindow.h \
    hwfsystemdoc.h \
    hoperorderwindow.h \
    hoperorderview.h \
    honlinescene.h \
    honlinetreewidget.h \
    hwfsystemmgr.h \
    honlinerefreshthread.h \
    hkerneltest.h \
    hupdatethread.h

FORMS    += \
    templatewindow.ui \
    wfsystemwindow.ui \
    onlinewindow.ui \
    operorderwindow.ui \
    hkerneltest.ui

RESOURCES += \
    images.qrc \
    pixmaps.qrc

unix{

    LIBS += -L ../lib -lH5IconGui -lH5IconHelp -ldatafile -lkernel -ldatafile
}

win32{
   LIBS += \
        ../lib/H5IconGui.lib \
        ../lib/H5IconHelp.lib \
        ../lib/datafile.lib \
        ../lib/kernel.lib \
        ../lib/datafile.lib
}
