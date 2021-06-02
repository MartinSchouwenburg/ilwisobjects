#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = featureoperations
TEMPLATE = lib

DEFINES += FEATUREOPERATIONS_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include \
    ./include/projections

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/buffer.cpp \
    source/featureoperationsmodule.cpp \
    source/gridding.cpp \
    source/line2polygon.cpp \
    source/pointrastercrossing.cpp \
    source/polygon2line.cpp \
    source/raster2point.cpp \
    source/raster2polygon.cpp \
    source/transformcoordinates.cpp


HEADERS += \
 include/buffer.h \
 include/featureoperationsmodule.h \
 include/gridding.h \
 include/line2polygon.h \
 include/pointrastercrossing.h \
 include/polygon2line.h \
 include/raster2point.h \
 include/raster2polygon.h \
 include/transformcoordinates.h



DISTFILES += \
    featureoperations.json
LIBS += -L$$OUTPUTPATH/ -lilwiscore
