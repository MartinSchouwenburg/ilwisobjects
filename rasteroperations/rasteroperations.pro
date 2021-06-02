#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = rasteroperations
TEMPLATE = lib

DEFINES += RASTEROPERATIONS_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include


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
  \
 source/aggregateraster.cpp \
 source/aggregaterasterstatistics.cpp \
 source/areanumbering.cpp \
 source/classifier.cpp \
 source/clusterraster.cpp \
 source/comboclassification.cpp \
 source/crossrasters.cpp \
 source/densifyraster.cpp \
 source/distanceraster.cpp \
 source/line2raster.cpp \
 source/linearrasterfilter.cpp \
 source/lookupindex.cpp \
 source/mannkendallsignificancetest.cpp \
 source/mirrorrotateraster.cpp \
 source/movingaverage.cpp \
 source/percentilegroups.cpp \
 source/percentilegroupscolumn.cpp \
 source/pointtoraster.cpp \
 source/polygontoraster.cpp \
 source/rankorderrasterfilter.cpp \
 source/rasterclassification.cpp \
 source/rasteroperationsmodule.cpp \
 source/rasterslicing.cpp \
 source/rasterstackfromattributes.cpp \
 source/rasterstretchoperation.cpp \
 source/rastertopoint.cpp \
 source/setrepresentation.cpp \
 source/stackminmaxfilter.cpp \
 source/timesat_nrs.cpp \
 source/zonalstatistics.cpp

HEADERS += \ \
    include/aggregateraster.h \
    include/aggregaterasterstatistics.h \
    include/areanumbering.h \
    include/classifier.h \
    include/clusterraster.h \
    include/comboclassification.h \
    include/crossrasters.h \
    include/densifyraster.h \
    include/distanceraster.h \
    include/line2raster.h \
    include/linearrasterfilter.h \
    include/lookupindex.h \
    include/mannkendallsignificancetest.h \
    include/mirrorrotateraster.h \
    include/movingaverage.h \
    include/percentilegroups.h \
    include/percentilegroupscolumn.h \
    include/pointtoraster.h \
    include/polygontoraster.h \
    include/rankorderrasterfilter.h \
    include/rasterclassification.h \
    include/rasteroperationsmodule.h \
    include/rasterslicing.h \
    include/rasterstackfromattributes.h \
    include/rasterstrechoperation.h \
    include/rastertopoint.h \
    include/setrepresentation.h \
    include/stackminmaxfilter.h \
    include/timesat_nrs.h \
    include/zonalstatistics.h


DISTFILES += \
    rasteroperations.json

LIBS += -L$$OUTPUTPATH/ -lilwiscore
