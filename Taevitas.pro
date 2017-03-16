
#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T14:48:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taevitas
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

linux {
 LIBS += -L "third_party/lib/" -lflycapture -Wl,-R -Wl,third_party/lib
}

SOURCES += src/main.cpp\
        src/mainwindow.cpp\
	src/cameramanager.cpp\
	src/recorder.cpp

HEADERS  += src/mainwindow.h\
	src/cameramanager.h\
        src/recorder.h \
    src/stdafx.h

INCLUDEPATH += third_party/include/flycapture/

FORMS    += src/forms/mainwindow.ui

DESTDIR = build
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = src/

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../Program Files/Point Grey Research/FlyCapture2/lib/' -lFlyCapture2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../Program Files/Point Grey Research/FlyCapture2/lib/' -lFlyCapture2d
else:unix: LIBS += -L$$PWD/'../../../Program Files/Point Grey Research/FlyCapture2/lib/' -lFlyCapture2

INCLUDEPATH += $$PWD/'../../../Program Files/Point Grey Research/FlyCapture2/include'
DEPENDPATH += $$PWD/'../../../Program Files/Point Grey Research/FlyCapture2/include'
