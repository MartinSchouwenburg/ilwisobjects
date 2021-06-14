#QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -std=gnu++11
#QMAKE_CXXFLAGS += -fext-numeric-literals
#QMAKE_CXXFLAGS += -Wno-unused-parameter
#QMAKE_CXXFLAGS += -Wno-sign-compare
#QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
#QMAKE_CXXFLAGS += -Wno-deprecated-declarations



CONFIG(debug, debug|release) {
CONF=debug
}

CONFIG(release, debug|release) {
CONF=release
QMAKE_CXXFLAGS_RELEASE += -O2
}



win32-msvc* {
    contains(QMAKE_TARGET.arch, x86_64) {
        QMAKE_CXXFLAGS_WARN_ON -= -w34267
        QMAKE_CXXFLAGS += -wd4267
        QMAKE_CXXFLAGS_WARN_ON -= wd4577
        COMPILER = msvc
        BOOST=../../external
        PREFIXSHARED=
        PREFIX_COMPILER=msvcx64_
        CORELIBPATH =msvcx64_ilwiscore
        LIB_EXTENSION =$$QMAKE_EXTENSION_SHLIB
        EXTERNAL=../../external
    }
}

linux{
    BOOST=/usr/include
    PREFIXSHARED=lib
    LIBS += -L/usr/lib -lgsl \
            -L/usr/lib -lgslcblas
    QMAKE_CFLAGS_ISYSTEM=-I
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    QMAKE_CXXFLAGS += -Wno-sign-compare
    QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
    QMAKE_CXXFLAGS += -Wno-deprecated-declarations
    PREFIX_COMPILER=gccx64_
    CORELIBPATH =gccx64_ilwiscore
    LIB_EXTENSION = so.1.0.0
    DEFINES +=COMPILER_GCC
    EXTERNAL= . #dummy
}

linux-g++{
   !contains(QT_ARCH, x86_64){
       LINUXLIB=/usr/lib/i386-linux-gnu/
    } else {
       LINUXLIB=/usr/lib/x86_64-linux-gnu/
   }
}



QT += sql network concurrent

INCLUDEPATH +=  ../ilwiscore/include\
                ../ilwiscore/include/ilwisobjects \
                ../ilwiscore/include/ilwisobjects/geometry \
                ../ilwiscore/include/util \
                ../ilwiscore/include/ilwisobjects/geometry/geodeticdatum \
                ../ilwiscore/include/ilwisobjects/geometry/projection \
                ../ilwiscore/include/ilwisobjects/geometry/coordinatesystem \
                ../ilwiscore/include/ilwisobjects/geometry/georeference \
                ../ilwiscore/include/ilwisobjects/coverage \
                ../ilwiscore/include/ilwisobjects/table \
                ../ilwiscore/include/ilwisobjects/operation/model \
                ../ilwiscore/include/ilwisobjects/operation \
                ../ilwiscore/include/ilwisobjects/operation/modeller \
                ../ilwiscore/include/ilwisobjects/workflow \
                ../ilwiscore/include/ilwisobjects/representation \
                ../ilwiscore/include/catalog \
                ../ilwiscore/include/ilwisobjects/domain \
                ../ilwiscore/include/geos/include\
                $$BOOST \
                $$EXTERNAL

OUTPUTPATH=$$clean_path($$PWD/generated/bin/$$PREFIX_COMPILER$$CONF)
LIBPATH=$$clean_path($$PWD/generated/objectfiles/$$PREFIX_COMPILER$$TARGET/$$CONF)
LIBPATH=$$replace(LIBPATH,/,$$DIR_SEPARATOR)
SOURCEDIR=$$clean_path($$PWD/$$TARGET/source)
INLIBPATH=$$LIBPATH/*.$$LIB_EXTENSION
INLIBPATH = $$replace(INLIBPATH,/,$$DIR_SEPARATOR)
OBJECTS_DIR = $$LIBPATH
OUTLIBPATH=dummy $$TARGET
MOC_DIR=$$LIBPATH

equals(TARGET, ilwiscore){
    OUTLIBPATH= $$OUTPUTPATH
}else {
    OUTLIBPATH= $$OUTPUTPATH/extensions/$$TARGET
}

exists($$PWD/$$TARGET/resources){
    SOURCE_RESOURCE = $$clean_path($$PWD/$$TARGET/resources)
    TARGET_RESOURCE_DIR=$$OUTLIBPATH
    SOURCE_RESOURCE = $$replace(SOURCE_RESOURCE,/,$$DIR_SEPARATOR)
    QMAKE_PRE_LINK += $$QMAKE_MKDIR $$TARGET_RESOURCE_DIR $$escape_expand(\n\t)
    QMAKE_PRE_LINK += $$QMAKE_COPY_DIR $$SOURCE_RESOURCE $$TARGET_RESOURCE_DIR $$escape_expand(\n\t)
}

OUTLIBPATH=$$replace(OUTLIBPATH,/,$$DIR_SEPARATOR)
DESTDIR=$$OUTLIBPATH








