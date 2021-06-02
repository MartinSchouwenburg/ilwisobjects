#-------------------------------------------------
#
# Project created by QtCreator 2021-03-19T08:50:35
#
#-------------------------------------------------

TARGET = baseoperations
TEMPLATE = lib

include(../global.pri)
INCLUDEPATH += ./include \
    ./include/data \
    ./include/conditions \
    ./include/creators \
    ./includes/features \
    ./include/geometry \
    ./include/math \
    ./include/util


DEFINES += BASEOPERATIONS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    baseoperations.json

HEADERS += \
    include/conditions/compare.h \
    include/conditions/iscompatible.h \
    include/conditions/junction.h \
    include/conditions/numbercondition.h \
    include/conditions/rangeoperation.h \
    include/creators/createboundsonlycsy.h \
    include/creators/createcombinationmatrix.h \
    include/creators/createcornersgeoreference.h \
    include/creators/createfeaturecoverage.h \
    include/creators/createidentifierdomain.h \
    include/creators/createintervaldomain.h \
    include/creators/createitemrepresentation.h \
    include/creators/createnumericdomain.h \
    include/creators/createpalettedomain.h \
    include/creators/createprojectedcoordinatesystem.h \
    include/creators/createrastercoverage.h \
    include/creators/createtable.h \
    include/creators/createthematicdomain.h \
    include/creators/createtimedomain.h \
    include/creators/createtimeintervaldomain.h \
    include/creators/createvaluerepresentation.h \
    include/creators/parsestackdefinition.h \
    include/data/addcolumn.h \
    include/data/addrasterband.h \
    include/data/aggregatetable.h \
    include/data/assignment.h \
    include/data/connect.h \
    include/data/convertcolumndomain.h \
    include/data/copycolumn.h \
    include/data/iffeature.h \
    include/data/iffraster.h \
    include/data/ifoperation.h \
    include/data/number2string.h \
    include/data/property.h \
    include/data/rasvalue.h \
    include/data/saveas.h \
    include/data/selection.h \
    include/data/selectionbase.h \
    include/data/selectionfeatures.h \
    include/data/selectiontable.h \
    include/data/serviceobject.h \
    include/data/setattributetabel.h \
    include/data/setvaluerange.h \
    include/data/setvariable.h \
    include/data/systemproperty.h \
    include/data/tablevalue.h \
    include/data/tablevaluebyprimarykey.h \
    include/feature/geometryoperations.h \
    include/geometry/coord2pixel.h \
    include/geometry/fcoordinate.h \
    include/geometry/fpixel.h \
    include/geometry/gridsize.h \
    include/geometry/mastergeoreference.h \
    include/geometry/pixel2coord.h \
    include/geometry/resampleraster.h \
    include/geometry/setgeoreference.h \
    include/geometry/spatialrelation.h \
    include/math/aggregation.h \
    include/math/binarylogical.h \
    include/math/binarymathfeature.h \
    include/math/binarymathraster.h \
    include/math/binarymathtable.h \
    include/math/calculatoroperation.h \
    include/math/columnjoin.h \
    include/math/columnunaryoperation.h \
    include/math/mapcalc.h \
    include/math/tabcalc.h \
    include/math/unarymath.h \
    include/math/unarymathoperations.h \
    include/math/unarymathrasterandnumber.h \
    include/math/unarymathtable.h \
    include/util/stringoperations.h \
    include/util/testoperation.h \
    include/util/text2output.h \
    include/util/workingcatalog.h \
    include/baseoperations_global.h \
    include/baseoperationsmodule.h

SOURCES += \
    source/conditions/compare.cpp \
    source/conditions/iscompatible.cpp \
    source/conditions/junction.cpp \
    source/conditions/numbercondition.cpp \
    source/conditions/rangeoperation.cpp \
    source/creators/createboundsonlycsy.cpp \
    source/creators/createcombinationmatrix.cpp \
    source/creators/createcornersgeoreference.cpp \
    source/creators/createfeaturecoverage.cpp \
    source/creators/createidentifierdomain.cpp \
    source/creators/createintervaldomain.cpp \
    source/creators/createitemrepresentation.cpp \
    source/creators/createnumericdomain.cpp \
    source/creators/createpalettedomain.cpp \
    source/creators/createprojectedcoordinatesystem.cpp \
    source/creators/createrastercoverage.cpp \
    source/creators/createtable.cpp \
    source/creators/createthematicdomain.cpp \
    source/creators/createtimedomain.cpp \
    source/creators/createtimeintervaldomain.cpp \
    source/creators/createvaluerepresentation.cpp \
    source/creators/parsestackdefinition.cpp \
    source/data/addcolumn.cpp \
    source/data/addrasterband.cpp \
    source/data/aggregatetable.cpp \
    source/data/assignment.cpp \
    source/data/connect.cpp \
    source/data/convertcolumndomain.cpp \
    source/data/copycolumn.cpp \
    source/data/iffeature.cpp \
    source/data/iffraster.cpp \
    source/data/ifoperation.cpp \
    source/data/number2string.cpp \
    source/data/property.cpp \
    source/data/rasvalue.cpp \
    source/data/saveas.cpp \
    source/data/selection.cpp \
    source/data/selectionbase.cpp \
    source/data/selectionfeatures.cpp \
    source/data/selectiontable.cpp \
    source/data/serviceobject.cpp \
    source/data/setattributetabel.cpp \
    source/data/setvaluerange.cpp \
    source/data/setvariable.cpp \
    source/data/systemproperty.cpp \
    source/data/tablevalue.cpp \
    source/data/tablevaluebyprimarykey.cpp \
    source/geometry/coord2pixel.cpp \
    source/geometry/fcoordinate.cpp \
    source/geometry/fpixel.cpp \
    source/geometry/gridsize.cpp \
    source/geometry/mastergeoreference.cpp \
    source/geometry/pixel2coord.cpp \
    source/geometry/resampleraster.cpp \
    source/geometry/setgeoreference.cpp \
    source/geometry/spatialrelation.cpp \
    source/math/aggregation.cpp \
    source/math/binarylogical.cpp \
    source/math/binarymathfeature.cpp \
    source/math/binarymathraster.cpp \
    source/math/binarymathtable.cpp \
    source/math/calculatoroperation.cpp \
    source/math/columnjoin.cpp \
    source/math/columnunaryoperation.cpp \
    source/math/mapcalc.cpp \
    source/math/tabcalc.cpp \
    source/math/unarymath.cpp \
    source/math/unarymathoperations.cpp \
    source/math/unarymathrasterandnumber.cpp \
    source/math/unarymathtable.cpp \
    source/util/stringoperations.cpp \
    source/util/testoperation.cpp \
    source/util/text2output.cpp \
    source/util/workingcatalog.cpp \
    source/baseoperationsmodule.cpp

LIBS += -L$$OUTPUTPATH/ -lilwiscore
#LIBS += -Lc:/ilwisobjects/proversion/generated/msvc64bit_debug_core/debug/ -lilwiscore

