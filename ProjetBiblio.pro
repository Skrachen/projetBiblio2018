#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetBiblio
TEMPLATE = app


# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
unix {
        LIBS     += -lGL -lGLU
}



SOURCES += main.cpp\
        widget.cpp \
    gestioncam.cpp \
    jeu.cpp \
    brique.cpp \
    mur.cpp \
    palet.cpp \
    balle.cpp \
    fond.cpp \
    cassebrique.cpp

HEADERS  += widget.h \
    gestioncam.h \
    jeu.h \
    brique.h \
    mur.h \
    palet.h \
    balle.h \
    fond.h \
    cassebrique.h

FORMS    += widget.ui

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_video2413 \
    -lopencv_features2d2413 \
    -lopencv_calib3d2413

RESOURCES += \
    image/ressource.qrc
