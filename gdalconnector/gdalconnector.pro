#-------------------------------------------------
#
# Project created by QtCreator 2021-03-24T09:19:22
#
#-------------------------------------------------

TARGET = gdalconnector
TEMPLATE = lib

DEFINES += GDALCONNECTOR_LIBRARY

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
    source/coordinatesystemconnector.cpp \
    source/coverageconnector.cpp \
    source/domainconnector.cpp \
    source/gdalcatalogexplorer.cpp \
    source/gdalcatalogfileexplorer.cpp \
    source/gdalconnector.cpp \
    source/gdalfeatureconnector.cpp \
    source/gdalfeaturetableconnector.cpp \
    source/gdalitem.cpp \
    source/gdalmodule.cpp \
    source/gdalobjectfactory.cpp \
    source/gdalproxy.cpp \
    source/gdaltableloader.cpp \
    source/georefconnector.cpp \
    source/gridcoverageconnector.cpp

HEADERS += \
    include/coordinatesystemconnector.h \
    include/coverageconnector.h \
    include/domainconnector.h \
    include/gdalcatalogexplorer.h \
    include/gdalcatalogfileexplorer.h \
    include/gdalconnector.h \
    include/gdalconnector_global.h \
    include/gdalfeatureconnector.h \
    include/gdalfeaturetableconnector.h \
    include/gdalitem.h \
    include/gdalmodule.h \
    include/gdalobjectfactory.h \
    include/gdalproxy.h \
    include/gdaltableloader.h \
    include/georefconnector.h \
    include/gridcoverageconnector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    gdalconnector.json \
    resources/GDALLogoBW.svg \
    resources/GDALLogoColor.svg \
    resources/GDALLogoGS.svg \
    resources/compdcs.csv \
    resources/coordinate_axis.csv \
    resources/cubewerx_extra.wkt \
    resources/datum_shift.csv \
    resources/default.rsc \
    resources/ecw_cs.wkt \
    resources/ellipsoid.csv \
    resources/epsg.wkt \
    resources/esri_StatePlane_extra.wkt \
    resources/esri_Wisconsin_extra.wkt \
    resources/esri_extra.wkt \
    resources/gcs.csv \
    resources/gcs.override.csv \
    resources/gdal_datum.csv \
    resources/gdalicon.png \
    resources/gdalvrt.xsd \
    resources/geoccs.csv \
    resources/gml_registry.xml \
    resources/gmlasconf.xml \
    resources/gmlasconf.xsd \
    resources/gt_datum.csv \
    resources/gt_ellips.csv \
    resources/header.dxf \
    resources/inspire_cp_BasicPropertyUnit.gfs \
    resources/inspire_cp_CadastralBoundary.gfs \
    resources/inspire_cp_CadastralParcel.gfs \
    resources/inspire_cp_CadastralZoning.gfs \
    resources/jpfgdgml_AdmArea.gfs \
    resources/jpfgdgml_AdmBdry.gfs \
    resources/jpfgdgml_AdmPt.gfs \
    resources/jpfgdgml_BldA.gfs \
    resources/jpfgdgml_BldL.gfs \
    resources/jpfgdgml_Cntr.gfs \
    resources/jpfgdgml_CommBdry.gfs \
    resources/jpfgdgml_CommPt.gfs \
    resources/jpfgdgml_Cstline.gfs \
    resources/jpfgdgml_ElevPt.gfs \
    resources/jpfgdgml_GCP.gfs \
    resources/jpfgdgml_LeveeEdge.gfs \
    resources/jpfgdgml_RailCL.gfs \
    resources/jpfgdgml_RdASL.gfs \
    resources/jpfgdgml_RdArea.gfs \
    resources/jpfgdgml_RdCompt.gfs \
    resources/jpfgdgml_RdEdg.gfs \
    resources/jpfgdgml_RdMgtBdry.gfs \
    resources/jpfgdgml_RdSgmtA.gfs \
    resources/jpfgdgml_RvrMgtBdry.gfs \
    resources/jpfgdgml_SBAPt.gfs \
    resources/jpfgdgml_SBArea.gfs \
    resources/jpfgdgml_SBBdry.gfs \
    resources/jpfgdgml_WA.gfs \
    resources/jpfgdgml_WL.gfs \
    resources/jpfgdgml_WStrA.gfs \
    resources/jpfgdgml_WStrL.gfs \
    resources/libraries.config \
    resources/netcdf_config.xsd \
    resources/nitf_spec.xml \
    resources/nitf_spec.xsd \
    resources/ogr_extensions.ini \
    resources/ogr_formats.config \
    resources/ogrvrt.xsd \
    resources/osmconf.ini \
    resources/ozi_datum.csv \
    resources/ozi_ellips.csv \
    resources/pci_datum.txt \
    resources/pci_ellips.txt \
    resources/pcs.csv \
    resources/pcs.override.csv \
    resources/plscenesconf.json \
    resources/prime_meridian.csv \
    resources/projop_wparm.csv \
    resources/ruian_vf_ob_v1.gfs \
    resources/ruian_vf_st_uvoh_v1.gfs \
    resources/ruian_vf_st_v1.gfs \
    resources/ruian_vf_v1.gfs \
    resources/s57agencies.csv \
    resources/s57attributes.csv \
    resources/s57attributes_aml.csv \
    resources/s57attributes_iw.csv \
    resources/s57expectedinput.csv \
    resources/s57objectclasses.csv \
    resources/s57objectclasses_aml.csv \
    resources/s57objectclasses_iw.csv \
    resources/seed_2d.dgn \
    resources/seed_3d.dgn \
    resources/stateplane.csv \
    resources/trailer.dxf \
    resources/unit_of_measure.csv \
    resources/vdv452.xml \
    resources/vdv452.xsd \
    resources/vertcs.csv \
    resources/vertcs.override.csv

LIBS += -L$$OUTPUTPATH/ -lilwiscore

win32{
    GDALLIBS=$$clean_path($$PWD/../../external/libraries/gdalconnector/*.*)
    GDALLIBS = $$replace(GDALLIBS,/,$$DIR_SEPARATOR)
    QMAKE_POST_LINK += $$COPY_DIR  $$GDALLIBS  $$OUTLIBPATH $$escape_expand(\n\t)
}







