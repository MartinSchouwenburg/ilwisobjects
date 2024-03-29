/*IlwisObjects is a framework for analysis, processing and visualization of remote sensing and gis data
Copyright (C) 2018  52n North

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "kernel.h"
#include "version.h"
#include "ilwisdata.h"
#include "geometries.h"
#include "coordinatesystem.h"
#include "georeference.h"
#include "georefimplementation.h"
#include "simpelgeoreference.h"
#include "cornersgeoreference.h"
#include "controlpoint.h"
#include "ctpgeoreference.h"
#include "eigen3/Eigen/LU"
#include "mathhelper.h"
#include "planarctpgeoreference.h"
#include "undeterminedgeoreference.h"
#include "connectorinterface.h"
#include "versionedserializer.h"
#include "factory.h"
#include "abstractfactory.h"
#include "versioneddatastreamfactory.h"
#include "coverageserializerv1.h"
#include "georefserializerv1.h"

using namespace Ilwis;
using namespace Stream;

GeorefSerializerV1::GeorefSerializerV1(QDataStream& stream, const QString &version) : VersionedSerializer(stream, version)
{
}


bool GeorefSerializerV1::store(IlwisObject *obj, const IOOptions &options)
{
    if (!VersionedSerializer::store(obj, options))
        return false;
    VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
    if (!factory)
        return false;

    GeoReference *grf = static_cast<GeoReference *>(obj);
    std::unique_ptr<DataInterface> csyStreamer(factory->create(Version::interfaceVersion41, itCOORDSYSTEM,_stream));
    if ( !csyStreamer)
        return false;
    csyStreamer->store(grf->coordinateSystem().ptr(),options);

    _stream << grf->size().xsize() << grf->size().ysize() << grf->size().zsize();
    _stream << grf->centerOfPixel();

    if ( grf->grfType<CornersGeoReference>()){
        _stream << CornersGeoReference::typeName();
        Envelope envelope = grf->envelope();
        _stream << envelope.min_corner().x << envelope.min_corner().y << envelope.max_corner().x << envelope.max_corner().y;
    } else if ( grf->grfType<CTPGeoReference>()){
        _stream << CTPGeoReference::typeName();
        QSharedPointer<PlanarCTPGeoReference> ctpgrf = grf->as<PlanarCTPGeoReference>();
        int nrOfControlPoints = ctpgrf->nrControlPoints();
        _stream << nrOfControlPoints;
        for(int i =0; i < nrOfControlPoints; ++i){
            _stream << ctpgrf->controlPoint(i).llLocation().x << ctpgrf->controlPoint(i).llLocation().y;
            _stream << ctpgrf->controlPoint(i).x << ctpgrf->controlPoint(i).y;
            _stream << ctpgrf->controlPoint(i).gridLocation().x << ctpgrf->controlPoint(i).gridLocation().y;
            _stream << ctpgrf->controlPoint(i).isActive();
        }
        _stream << (int)ctpgrf->transformation();
		_stream << grf->resourceRef()["slaveraster"].toString();
    } else if ( grf->grfType<UndeterminedGeoReference>()){
         _stream << UndeterminedGeoReference::typeName();
    }
    return true;

}

bool GeorefSerializerV1::loadMetaData(IlwisObject *obj, const IOOptions &options)
{
    if (!VersionedSerializer::loadMetaData(obj, options))
        return false;

    VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
    if (!factory)
        return false;

    quint64 type;
    QString version;
    _stream >> type;
    _stream >> version;

    std::unique_ptr<DataInterface> csyStreamer(factory->create(version, itCOORDSYSTEM,_stream));
    if ( !csyStreamer)
        return false;
    GeoReference *grf = static_cast<GeoReference *>(obj);
    ICoordinateSystem csy(type);
    csyStreamer->loadMetaData(csy.ptr(),options);


    quint32 xsize, ysize, zsize;
    _stream >> xsize >> ysize >> zsize;

    bool centerofpixels;
    _stream >> centerofpixels;

    QString typeName;
    _stream >> typeName;
    if ( typeName == CornersGeoReference::typeName()){
        double minx, miny, maxx, maxy;
        _stream >> minx >> miny >> maxx >> maxy;
        CornersGeoReference *cornersgrf = new CornersGeoReference();
        cornersgrf->internalEnvelope(Envelope(Coordinate(minx, miny), Coordinate(maxx, maxy)));
        grf->impl(cornersgrf);
    } else if ( typeName == CTPGeoReference::typeName() ){
        PlanarCTPGeoReference *ctpgrf = new PlanarCTPGeoReference();
        int nrOfControlPoints;
        _stream >> nrOfControlPoints;
        for(int i = 0; i < nrOfControlPoints; ++i){
            ControlPoint pnt;
            double x,y;
            _stream >> x >> y;
            LatLon ll;
            ll.x = x;
            ll.y = y;
            pnt.llLocation(ll);
            _stream >> x >> y;
            pnt.x = x;
            pnt.y = y;
            _stream >> x >> y;
            Pixeld pix(x,y);
            pnt.gridLocation(pix);
            bool active;
            _stream >> active;
            pnt.active(active);;
            ctpgrf->setControlPoint(pnt);
        }
        int transformation;
        _stream >> transformation;
        ctpgrf->transformation((PlanarCTPGeoReference::Transformation)transformation);
        grf->impl(ctpgrf);
		QString slave;
		_stream >> slave;
		grf->resourceRef().addProperty("slaveraster", slave);
    }else{
        grf->impl( new UndeterminedGeoReference());
    }
    grf->size(Size<>(xsize, ysize, zsize));
    grf->coordinateSystem(csy);
    grf->centerOfPixel(centerofpixels);
    grf->compute();

    return true;

}

VersionedSerializer *GeorefSerializerV1::create(QDataStream &stream, const QString &version)
{
    return new GeorefSerializerV1(stream, version);
}
