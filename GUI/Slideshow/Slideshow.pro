#-------------------------------------------------
#
# Project created by QtCreator 2017-06-26T22:23:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Slideshow
TEMPLATE = app
DESTDIR = debug # Executable file directory
OBJECTS_DIR = debug # Intermediate object files directory
MOC_DIR = debug # Intermediate moc files directory
RCC_DIR = debug # Qt Resource Compiler output files directory

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ../../main.cpp \
    Slideshow.cpp \
    ImageView.cpp \
    DotsContainer.cpp \
    ImagePath.cpp

HEADERS += \
    Slideshow.h \
    ImageView.h \
    DotsContainer.h \
    ImagePath.h

FORMS += \
    Slideshow.ui

RESOURCES += \
    slideshow.qrc
