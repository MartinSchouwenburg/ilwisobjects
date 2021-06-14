#-------------------------------------------------
#
# Project created by QtCreator 2021-03-23T10:50:24
#
#-------------------------------------------------

TARGET = ilwis4connector
TEMPLATE = lib

DEFINES += ILWIS4CONNECTOR_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include \
    ./include/projections \
    ./include/qtcsv \
    ../../external

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
   source/ilwis4catalogexplorer.cpp \
   source/ilwis4connector.cpp \
   source/ilwis4coordinatesystemconnector.cpp \
   source/ilwis4domainconnector.cpp \
   source/ilwis4featureconnector.cpp \
   source/ilwis4georefconnector.cpp \
   source/ilwis4objectfactory.cpp \
   source/ilwis4rasterconnector.cpp \
   source/ilwis4representationconnector.cpp \
   source/ilwis4scriptconnector.cpp \
   source/ilwis4tableconnector.cpp \
   source/ilwis4workflowconnector.cpp \
   source/iwis4connectormodule.cpp \
   source/qtcsv/contentiterator.cpp \
   source/qtcsv/reader.cpp \
   source/qtcsv/stringdata.cpp \
   source/qtcsv/variantdata.cpp \
   source/qtcsv/writer.cpp

HEADERS += \
   \
  include/ilwis4catalogexplorer.h \
  include/ilwis4connector.h \
  include/ilwis4coordinatesystemconnector.h \
  include/ilwis4domainconnector.h \
  include/ilwis4featureconnector.h \
  include/ilwis4georefconnector.h \
  include/ilwis4objectfactory.h \
  include/ilwis4rasterconnector.h \
  include/ilwis4representationconnector.h \
  include/ilwis4scriptconnector.h \
  include/ilwis4tableconnector.h \
  include/ilwis4workflowconnector.h \
  include/iwis4connectormodule.h \
  include/qtcsv/abstractdata.h \
  include/qtcsv/qtcsv_global.h \
  include/qtcsv/reader.h \
  include/qtcsv/stringdata.h \
  include/qtcsv/variantdata.h \
  include/qtcsv/writer.h \
  source/qtcsv/contentiterator.h \
  source/qtcsv/filechecker.h \
  source/qtcsv/symbols.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ilwis4connector.json \
    resources/ilwis4formats.config

LIBS += -L$$OUTPUTPATH/ -lilwiscore
