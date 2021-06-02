#-------------------------------------------------
#
# Project created by QtCreator 2021-03-24T08:40:09
#
#-------------------------------------------------

TARGET = projectionimplproj4
TEMPLATE = lib

DEFINES += PROJECTIONIMPLPROJ4_LIBRARY

include(../global.pri)
INCLUDEPATH += ./include \
    ./proj4/src

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
    proj4/src/PJ_aea.c \
    proj4/src/PJ_aeqd.c \
    proj4/src/PJ_airy.c \
    proj4/src/PJ_aitoff.c \
    proj4/src/PJ_august.c \
    proj4/src/PJ_bacon.c \
    proj4/src/PJ_bipc.c \
    proj4/src/PJ_boggs.c \
    proj4/src/PJ_bonne.c \
    proj4/src/PJ_cass.c \
    proj4/src/PJ_cc.c \
    proj4/src/PJ_cea.c \
    proj4/src/PJ_chamb.c \
    proj4/src/PJ_collg.c \
    proj4/src/PJ_crast.c \
    proj4/src/PJ_denoy.c \
    proj4/src/PJ_eck1.c \
    proj4/src/PJ_eck2.c \
    proj4/src/PJ_eck3.c \
    proj4/src/PJ_eck4.c \
    proj4/src/PJ_eck5.c \
    proj4/src/PJ_eqc.c \
    proj4/src/PJ_eqdc.c \
    proj4/src/PJ_fahey.c \
    proj4/src/PJ_fouc_s.c \
    proj4/src/PJ_gall.c \
    proj4/src/PJ_geos.c \
    proj4/src/PJ_gins8.c \
    proj4/src/PJ_gn_sinu.c \
    proj4/src/PJ_gnom.c \
    proj4/src/PJ_goode.c \
    proj4/src/PJ_gstmerc.c \
    proj4/src/PJ_hammer.c \
    proj4/src/PJ_hatano.c \
    proj4/src/PJ_healpix.c \
    proj4/src/PJ_igh.c \
    proj4/src/PJ_imw_p.c \
    proj4/src/PJ_isea.c \
    proj4/src/PJ_krovak.c \
    proj4/src/PJ_labrd.c \
    proj4/src/PJ_laea.c \
    proj4/src/PJ_lagrng.c \
    proj4/src/PJ_larr.c \
    proj4/src/PJ_lask.c \
    proj4/src/PJ_lcc.c \
    proj4/src/PJ_lcca.c \
    proj4/src/PJ_loxim.c \
    proj4/src/PJ_lsat.c \
    proj4/src/PJ_mbt_fps.c \
    proj4/src/PJ_mbtfpp.c \
    proj4/src/PJ_mbtfpq.c \
    proj4/src/PJ_merc.c \
    proj4/src/PJ_mill.c \
    proj4/src/PJ_mod_ster.c \
    proj4/src/PJ_moll.c \
    proj4/src/PJ_natearth.c \
    proj4/src/PJ_nell.c \
    proj4/src/PJ_nell_h.c \
    proj4/src/PJ_nocol.c \
    proj4/src/PJ_nsper.c \
    proj4/src/PJ_nzmg.c \
    proj4/src/PJ_ob_tran.c \
    proj4/src/PJ_ocea.c \
    proj4/src/PJ_oea.c \
    proj4/src/PJ_omerc.c \
    proj4/src/PJ_ortho.c \
    proj4/src/PJ_poly.c \
    proj4/src/PJ_putp2.c \
    proj4/src/PJ_putp3.c \
    proj4/src/PJ_putp4p.c \
    proj4/src/PJ_putp5.c \
    proj4/src/PJ_putp6.c \
    proj4/src/PJ_robin.c \
    proj4/src/PJ_rpoly.c \
    proj4/src/PJ_sconics.c \
    proj4/src/PJ_somerc.c \
    proj4/src/PJ_stere.c \
    proj4/src/PJ_sterea.c \
    proj4/src/PJ_sts.c \
    proj4/src/PJ_tcc.c \
    proj4/src/PJ_tcea.c \
    proj4/src/PJ_tmerc.c \
    proj4/src/PJ_tpeqd.c \
    proj4/src/PJ_urm5.c \
    proj4/src/PJ_urmfps.c \
    proj4/src/PJ_vandg.c \
    proj4/src/PJ_vandg2.c \
    proj4/src/PJ_vandg4.c \
    proj4/src/PJ_wag2.c \
    proj4/src/PJ_wag3.c \
    proj4/src/PJ_wag7.c \
    proj4/src/PJ_wink1.c \
    proj4/src/PJ_wink2.c \
    proj4/src/aasincos.c \
    proj4/src/adjlon.c \
    proj4/src/bch2bps.c \
    proj4/src/bchgen.c \
    proj4/src/biveval.c \
    proj4/src/dmstor.c \
    proj4/src/emess.c \
    proj4/src/gen_cheb.c \
    proj4/src/geocent.c \
    proj4/src/geod_for.c \
    proj4/src/geod_inv.c \
    proj4/src/geod_set.c \
    proj4/src/hypot.c \
    proj4/src/mk_cheby.c \
    proj4/src/nad_cvt.c \
    proj4/src/nad_init.c \
    proj4/src/nad_intr.c \
    proj4/src/p_series.c \
    proj4/src/pj_apply_gridshift.c \
    proj4/src/pj_apply_vgridshift.c \
    proj4/src/pj_auth.c \
    proj4/src/pj_ctx.c \
    proj4/src/pj_datum_set.c \
    proj4/src/pj_datums.c \
    proj4/src/pj_deriv.c \
    proj4/src/pj_ell_set.c \
    proj4/src/pj_ellps.c \
    proj4/src/pj_errno.c \
    proj4/src/pj_factors.c \
    proj4/src/pj_fwd.c \
    proj4/src/pj_gauss.c \
    proj4/src/pj_geocent.c \
    proj4/src/pj_gridinfo.c \
    proj4/src/pj_gridlist.c \
    proj4/src/pj_init.c \
    proj4/src/pj_initcache.c \
    proj4/src/pj_inv.c \
    proj4/src/pj_latlong.c \
    proj4/src/pj_list.c \
    proj4/src/pj_log.c \
    proj4/src/pj_malloc.c \
    proj4/src/pj_mlfn.c \
    proj4/src/pj_msfn.c \
    proj4/src/pj_mutex.c \
    proj4/src/pj_open_lib.c \
    proj4/src/pj_param.c \
    proj4/src/pj_phi2.c \
    proj4/src/pj_pr_list.c \
    proj4/src/pj_qsfn.c \
    proj4/src/pj_release.c \
    proj4/src/pj_strerrno.c \
    proj4/src/pj_transform.c \
    proj4/src/pj_tsfn.c \
    proj4/src/pj_units.c \
    proj4/src/pj_utils.c \
    proj4/src/pj_zpoly1.c \
    proj4/src/proj.c \
    proj4/src/proj_etmerc.c \
    proj4/src/proj_mdist.c \
    proj4/src/proj_rouss.c \
    proj4/src/rtodms.c \
    proj4/src/vector1.c \
    source/prjimplfactoryproj4.cpp \
    source/prjimplproj4.cpp \
    source/projectionmodule.cpp

HEADERS += \
    include/prjimplproj4.h \
    include/prjmplfactoryproj4.h \
    include/projectionImplProj4_global.h \
    include/projectionmodule.h \
    proj4/src/emess.h \
    proj4/src/geocent.h \
    proj4/src/geodesic.h \
    proj4/src/nad_list.h \
    proj4/src/org_proj4_PJ.h \
    proj4/src/org_proj4_Projections.h \
    proj4/src/pj_list.h \
    proj4/src/proj_api.h \
    proj4/src/projects.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$OUTPUTPATH/ -lilwiscore

DISTFILES += \
    projectionImplProj4.json
