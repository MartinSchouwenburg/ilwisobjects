#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = internalconnector
TEMPLATE = lib

DEFINES += INTERNALCONNECTOR_LIBRARY

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
    source/internalcatalogexplorer.cpp \
    source/internalcombinationmatrixconnector.cpp \
    source/internalcoordinatesystemconnector.cpp \
    source/internaldomain.cpp \
    source/internalellipsoidconnector.cpp \
    source/internalfeaturecoverageconnector.cpp \
    source/internalgeoreferenceconnector.cpp \
    source/internalilwisobjectfactory.cpp \
    source/internalmodelconnector.cpp \
    source/internalmodule.cpp \
    source/internalprjimplfactory.cpp \
    source/internalprojectionconnector.cpp \
    source/internalrastercoverageconnector.cpp \
    source/internalrepresentation.cpp \
    source/internalscriptconnector.cpp \
    source/internaltableconnector.cpp \
    source/operationmetadataconnector.cpp \
    source/projections/cylindsinusinterrupt2.cpp \
    source/projections/dutchrd.cpp \
    source/projections/platecaree.cpp \
    source/projections/projectionimplementationinternal.cpp \
    source/workflowconnector.cpp

HEADERS += \
    include/epsg.h \
    include/internalcatalogexplorer.h \
    include/internalcombinationmatrixconnector.h \
    include/internalcoordinatesystemconnector.h \
    include/internaldomain.h \
    include/internalellipsoidconnector.h \
    include/internalfeaturecoverageconnector.h \
    include/internalgeoreferenceconnector.h \
    include/internalilwisobjectfactory.h \
    include/internalmodelconnector.h \
    include/internalmodule.h \
    include/internalprjmplfactory.h \
    include/internalprojectionconnector.h \
    include/internalrastercoverageconnector.h \
    include/internalrepresentation.h \
    include/internalscriptconnector.h \
    include/internaltableconnector.h \
    include/operationmetadataconnector.h \
    include/projections/cylindsinusinterrupt2.h \
    include/projections/dutchrd.h \
    include/projections/platecaree.h \
    include/projections/projectionimplementationinternal.h \
    include/workflowconnector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    internalconnector.json

LIBS += -L$$OUTPUTPATH/ -lilwiscore
