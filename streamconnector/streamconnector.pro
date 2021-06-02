#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = streamconnector
TEMPLATE = lib

DEFINES += STREAMCONNECTOR_LIBRARY

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
    source/catalogconnection.cpp \
    source/catalogserializerv1.cpp \
    source/combinationmatrixserializerv1.cpp \
    source/coordinatesystemserializerv1.cpp \
    source/coverageserializerv1.cpp \
    source/domainserializerv1.cpp \
    source/downloadmanager.cpp \
    source/ellipsoidserializerv1.cpp \
    source/featureserializerv1.cpp \
    source/georefserializerv1.cpp \
    source/modelserializerv1.cpp \
    source/operationmetadataserializerv1.cpp \
    source/projectionserializerv1.cpp \
    source/rasterserializerv1.cpp \
    source/rawconverter.cpp \
    source/representationserializer.cpp \
    source/scriptserializerv1.cpp \
    source/streamcatalogexplorer.cpp \
    source/streamconnector.cpp \
    source/streammodule.cpp \
    source/streamobjectfactory.cpp \
    source/tableserializerv1.cpp \
    source/versioneddatastreamfactory.cpp \
    source/versionedserializer.cpp \
    source/workflowserializerv1.cpp


HEADERS += \
    include/catalogconnection.h \
    include/catalogserializerv1.h \
    include/combinationmatrixserializerv1.h \
    include/coordinatesystemserializerv1.h \
    include/coverageserializerv1.h \
    include/domainserializerv1.h \
    include/downloadmanager.h \
    include/ellipsoidserializerv1.h \
    include/featureserializerv1.h \
    include/georefserializerv1.h \
    include/modelserializerv1.h \
    include/operationmetadataserializerv1.h \
    include/projectionserializerv1.h \
    include/rasterserializerv1.h \
    include/rawconverter.h \
    include/representationserializer.h \
    include/scriptserializerv1.h \
    include/streamcatalogexplorer.h \
    include/streamconnector.h \
    include/streammodule.h \
    include/streamobjectfactory.h \
    include/tableserializerv1.h \
    include/versioneddatastreamfactory.h \
    include/versionedserializer.h \
    include/workflowserializerv1.h


DISTFILES += \
    streamconnector.json \
    resources/streamformats.config

LIBS += -L$$OUTPUTPATH/ -lilwiscore
