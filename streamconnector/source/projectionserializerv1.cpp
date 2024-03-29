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
#include "geometries.h"
#include "ilwisdata.h"
#include "ellipsoid.h"
#include "projection.h"
#include "factory.h"
#include "abstractfactory.h"
#include "projectionfactory.h"
#include "connectorinterface.h"
#include "versionedserializer.h"
#include "projectionserializerv1.h"

using namespace Ilwis;
using namespace Stream;

VersionedSerializer *ProjectionSerializerV1::create(QDataStream& stream, const QString &version)
{
    return new ProjectionSerializerV1(stream, version);
}

ProjectionSerializerV1::ProjectionSerializerV1(QDataStream &stream, const QString &version) : VersionedSerializer(stream, version)
{
}

bool ProjectionSerializerV1::store(IlwisObject *obj, const IOOptions &options)
{
    if (!VersionedSerializer::store(obj, options))
        return false;
    Projection *proj = static_cast<Projection *>(obj);
    QString proj4Def = proj->toProj4();
    _stream << proj4Def;
    _stream << proj->authority();
    return true;

}

bool ProjectionSerializerV1::loadMetaData(IlwisObject *obj, const IOOptions &options)
{
    if (!VersionedSerializer::loadMetaData(obj, options))
        return false;
    const ProjectionFactory *factory =  kernel()->factory<ProjectionFactory>("ProjectionFactory","proj4");
    if ( !factory)
        return false;
    Projection *proj = static_cast<Projection *>(obj);
    QString proj4Def;
    _stream >> proj4Def;
    QString projtype = proj->code();
    ProjectionImplementation *impl = factory->create(projtype, proj4Def) ;
    if (!impl)
        return false;
    proj->setImplementation(impl);
    QString authority;
    _stream >> authority;
    proj->setAuthority(authority);
    return true;
}
