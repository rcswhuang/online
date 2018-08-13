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
    hpreviewwindow.cpp \
    #htemplatewindow.cpp \
    #hwfsystemtview.cpp \
    #htemplateview.cpp \
    hwfsystemwindow.cpp \
    hwfsystemdoc.cpp \
    hwfsystemmgr.cpp \
    honlinetreewidget.cpp \
    hoperorderview.cpp \
    honlinerefreshthread.cpp \
    hkerneltest.cpp \
    hupdatethread.cpp \
    hopsheet.cpp \
    hgraphicsscene.cpp \
    hgraphicsview.cpp \
    hframe.cpp \
    hgraphframe.cpp

HEADERS  += \
    #htemplatewindow.h \
    #hwfsystemtview.h \
    #htemplateview.h \
    hwfsystemwindow.h \
    hwfsystemdoc.h \
    hoperorderwindow.h \
    hoperorderview.h \
    honlinetreewidget.h \
    hwfsystemmgr.h \
    honlinerefreshthread.h \
    hkerneltest.h \
    hupdatethread.h \
    hopsheet.h \
    hgraphicsscene.h \
    hgraphicsview.h \
    hframe.h \
    hgraphframe.h

FORMS    += \
    templatewindow.ui \
    wfsystemwindow.ui \
    operorderwindow.ui \
    hkerneltest.ui \
    graphframe.ui

RESOURCES += \
    images.qrc \
    pixmaps.qrc

unix{

    LIBS += -L ../lib -lH5IconGui -lH5IconHelp -ldatafile -lkernel
}

win32{
   LIBS += \
        ../lib/H5IconGui.lib \
        ../lib/H5IconHelp.lib \
        ../lib/datafile.lib \
        ../lib/kernel.lib \
        ../lib/datafile.lib
}
