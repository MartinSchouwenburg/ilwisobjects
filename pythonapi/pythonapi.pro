#-------------------------------------------------
#
# Project created by QtCreator 2021-03-24T12:24:19
#
#-------------------------------------------------

TARGET = pythonapi
TEMPLATE = lib

DEFINES += PYTHONAPI_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include
PYMINORVERSION=8
win32{
    PYTHONLOCALDIR=$$clean_path($$PWD/../../external/libraries/python/)
    LIBS += -L$$PYTHONLOCALDIR/libs -lpython3$$PYMINORVERSION
    PYTHON_INCLUDE_FILES=../../external/python3$$PYMINORVERSION/include
}
linux {
    PYTHON_INCLUDE_FILES =/usr/include/python3.$$PYMINORVERSION
    LIBS += -L$$/usr/libs -lpython3.$$PYMINORVERSION
    CONFIG(debug, debug|debug) {
        OUTPUTPATHPYTHON = /home/$$(USER)/.local/lib/python3.$$PYMINORVERSION/site-packages/
    }
    CONFIG(release, debug|release) {
        OUTPUTPATHPYTHON=/usr/local/lib/python3.8/dist-packages/
    }
}

INCLUDEPATH += $$PYTHON_INCLUDE_FILES
QT += core

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += SWIG_PYTHON_INTERPRETER_NO_DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    include/ilwisobjects_wrap.cxx \
    source/pythonapi_booleanobject.cpp \
    source/pythonapi_catalog.cpp \
    source/pythonapi_collection.cpp \
    source/pythonapi_columndefinition.cpp\
    source/pythonapi_coordinatesystem.cpp \
    source/pythonapi_coverage.cpp \
    source/pythonapi_datadefinition.cpp \
    source/pythonapi_domain.cpp \
    source/pythonapi_domainitem.cpp \
    source/pythonapi_engine.cpp \
    source/pythonapi_error.cpp \
    source/pythonapi_extension.cpp \
    source/pythonapi_feature.cpp \
    source/pythonapi_featurecoverage.cpp \
    source/pythonapi_featureiterator.cpp \
    source/pythonapi_geometry.cpp \
    source/pythonapi_georeference.cpp \
    source/pythonapi_ilwisobject.cpp \
    source/pythonapi_pixeliterator.cpp \
    source/pythonapi_pyobject.cpp \
    source/pythonapi_qissuelogger.cpp \
    source/pythonapi_qvariant.cpp \
    source/pythonapi_range.cpp \
    source/pythonapi_rangeiterator.cpp \
    source/pythonapi_rastercoverage.cpp \
    source/pythonapi_table.cpp \
    source/pythonapi_util.cpp \
    source/pythonapi_vertexiterator.cpp

HEADERS += \
    include/ilwisobjects.i \
    include/pythonapi_booleanobject.h \
    include/pythonapi_catalog.h \
    include/pythonapi_collection.h \
    include/pythonapi_columndefinition.h \
    include/pythonapi_coordinatesystem.h \
    include/pythonapi_coverage.h \
    include/pythonapi_datadefinition.h \
    include/pythonapi_domain.h \
    include/pythonapi_domainitem.h \
    include/pythonapi_engine.h \
    include/pythonapi_error.h \
    include/pythonapi_extension.h \
    include/pythonapi_feature.h \
    include/pythonapi_featurecoverage.h \
    include/pythonapi_featureiterator.h \
    include/pythonapi_geometry.h \
    include/pythonapi_georeference.h \
    include/pythonapi_global.h \
    include/pythonapi_ilwisobject.h \
    include/pythonapi_object.h \
    include/pythonapi_pixeliterator.h \
    include/pythonapi_pyobject.h \
    include/pythonapi_qissuelogger.h \
    include/pythonapi_qtGNUTypedefs.h \
    include/pythonapi_qvariant.h \
    include/pythonapi_range.h \
    include/pythonapi_rangeiterator.h \
    include/pythonapi_rastercoverage.h \
    include/pythonapi_table.h \
    include/pythonapi_util.h \
    include/pythonapi_vertexiterator.h \

LIBS += -L$$OUTPUTPATH/ -lilwiscore

COPY_FILES = ilwisobjects.py paths.py

linux {
   swig.target = $$LIBPATH/ilwisobjects.py
    swig.commands = swig3.0 -python -c++ $$PWD/include/ilwisobjects.i
    swig.depends = $$PWD/include/ilwisobjects.i $$PWD/include/*.h $$PWD/source/*.cpp
    QMAKE_EXTRA_TARGETS += swig
    PRE_TARGETDEPS += $$LIBPATH/ilwisobjects.py
    DEST_DIR = $$clean_path($$DESTDIR)
    QMAKE_RPATHDIR = $${OUTPUTPATHPYTHON}ilwis
    QMAKE_POST_LINK += $$quote(test -d $$OUTPUTPATHPYTHON || mkdir -p $$OUTPUTPATHPYTHON$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(cat $$PWD/include/paths.py $$PWD/include/ilwisobjects.py > $$DEST_DIR/temp.py$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$QMAKE_MKDIR $${OUTPUTPATHPYTHON}ilwis $$escape_expand(\n\t)
    QMAKE_POST_LINK += mv -f $$DEST_DIR/temp.py $${OUTPUTPATHPYTHON}ilwis/__init__.py$$escape_expand(\n\t)
    QMAKE_POST_LINK += cp -R -f  $$OUTPUTPATH/extensions/pythonapi/libpythonapi.so.1.0.0 $${OUTPUTPATHPYTHON}ilwis/_ilwisobjects.so$$escape_expand(\n\t)
    CONFIG(debug, debug|release) {
        QMAKE_POST_LINK += cp -R -f  $$OUTPUTPATH/* $${OUTPUTPATHPYTHON}ilwis$$escape_expand(\n\t)
    }
    CONFIG(release, debug|release){
        instfiles.path = $$OUTPUTPATHPYTHON/ilwis
        instfiles.files = $$clean_path($$OUTPUTPATH/*)
        INSTALLS += instfiles
    }
}
win32 {
    PYTHONSCRIPT_DIR=$$OUTPUTPATH/extensions/pythonscript/python/Lib/site-packages/ilwis
    PYTHONSCRIPT_DIR=$$replace(PYTHONSCRIPT_DIR,/,$$DIR_SEPARATOR)
    swig.target = $$LIBPATH/ilwisobjects.py
    SWIGPATH = $$clean_path($$PWD/../../external/programs/swigwin/swig.exe)
    SWIGPATH =  $$SWIGPATH -python -c++ -outdir $$LIBPATH -o $$SOURCEDIR/ilwisobjects_wrap.cxx  $$clean_path($$PWD/include/ilwisobjects.i)
    swig.commands = $$SWIGPATH
    swig.depends = $$clean_path($$PWD/include/ilwisobjects.i $$PWD/include/*.h $$PWD/source/*.cpp)
    QMAKE_EXTRA_TARGETS += swig
    PRE_TARGETDEPS += $$LIBPATH/ilwisobjects.py
   # installer_script.files = pythonapi/installerPy.nsi
   # installer_script.path = $$PWD/../output/$$PLATFORM$$CONF
   # installer.commands = $$quote(C:\\Program Files (x86)\\NSIS\\makensis.exe) /V4 $$PWD/../output/$$PLATFORM$$CONF/installerPy.nsi
   # installer.path = $$PWD/../output/$$PLATFORM$$CONF
   # INSTALLS += installer_script installer
    QMAKE_POST_LINK += $$quote(echo f | xcopy /q /y /i $$LIBPATH\\$${TARGET}.$${QMAKE_EXTENSION_SHLIB} $$PYTHONSCRIPT_DIR\\_ilwisobjects.pyd$$escape_expand(\n\t))
    QMAKE_POST_LINK += $$quote(copy /y /b $$LIBPATH\\ilwisobjects.py $$PYTHONSCRIPT_DIR\\__init__.py$$escape_expand(\n\t))
}

DISTFILES += \
    include/paths.py


