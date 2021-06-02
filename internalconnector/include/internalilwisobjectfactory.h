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

#ifndef INTERNALOBJECTFACTORY_H
#define INTERNALOBJECTFACTORY_H

#include "size.h"

namespace Ilwis {

class Coverage;
class GeodeticDatum;
class GeoReference;
class Domain;
class NumericDomain;
class CoordinateSystem;
typedef IlwisData<CoordinateSystem> ICoordinateSystem;

namespace Internal {
/*!
 \brief factory used to create IlwisObjects that do not come from an external source

 There are a number of IlwisObject that are based on internal definitions. Many objects in the realm of
 spatial reference system are based on known defaults and thus are generated from a set of internal tables.
Furthermore there are a number of objects that are default to the system (e.g. domain Image). They are
also generated by the internal object factories.

*/
class InternalIlwisObjectFactory : public IlwisObjectFactory
{
public:
    InternalIlwisObjectFactory();

    virtual Ilwis::IlwisObject *create(const Resource & resource,const IOOptions& options=IOOptions()) const;
    virtual IlwisObject *create(IlwisTypes type, const QString &subtype=sUNDEF) const;
    bool canUse(const Ilwis::Resource &resource) const;

private:
    IlwisObject *createEllipsoid(const Resource &resource, const IOOptions &options) const;
    GeodeticDatum *createDatum(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createProjection(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createEllipsoidFromQuery(const QString &query, const Resource& resource) const;
    IlwisObject *createDomain(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createCsyFromCode(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createRasterCoverage(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createTable(const Resource &resource, const IOOptions &options) const;
    IlwisObject *createOperationMetaData(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createWorkflow(const Resource &resource, const IOOptions &options) const;
    IlwisObject *createScript(const Resource &resource, const IOOptions &options) const;
    IlwisObject *createModel(const Resource &resource, const IOOptions &options) const;
    IlwisObject *createGeoreference(const Resource &resource, const Ilwis::IOOptions &options) const;
    bool createCoverage(const Ilwis::Resource &resource, Coverage *coverage, const Ilwis::IOOptions &options) const;
    IlwisObject *createFeatureCoverage(const Resource &resource, const Ilwis::IOOptions &options) const;
    IlwisObject *createCatalog(const Resource &resource, const Ilwis::IOOptions &options) const;
    GeoReference *createGrfFromCode(const Ilwis::Resource &resource) const;
    IlwisObject *createCsy(const Resource &resource, const IOOptions &options) const;
    IlwisObject *createRepresentation(const Resource &resource, const IOOptions &options) const;
    Domain *createItemDomain(Ilwis::InternalDatabaseConnection &db, const IOOptions &options, const Resource &resource) const;
    NumericDomain *createNumericDomain(const QString &code, Ilwis::InternalDatabaseConnection &db, const IOOptions &options, const Resource &resource) const;
    IlwisObject *createCombinationMatrix(const Resource &resource, const IOOptions &options) const;

    template<class T> T *createFromResource(const Resource& resource, const IOOptions &options) const{
        T *obj = new T(resource);
        const ConnectorFactory *factory = kernel()->factory<ConnectorFactory>("ilwis::ConnectorFactory");
        ConnectorInterface *connector = factory->createFromResource<>(resource, "internal");
        obj->setConnector(connector,IlwisObject::cmINPUT, options);
        obj->createTime(Time::now());
        obj->modifiedTime(Time::now());

        return obj;
    }

	template<class T> void variant2size(const QVariant& v, T& sz) const {
		QString typenm = v.typeName();
		if (typenm == "Ilwis::Size<quint32>") {
                        Size<quint32> isize = v.value<Size<quint32>>();
			sz = T(isize.xsize(), isize.ysize(), isize.zsize());
		}
		else if (typenm == "Ilwis::Size<qint32>") {
			Size<qint32> isize = v.value<Size<qint32>>();
			sz = T(isize.xsize(), isize.ysize(), isize.zsize());
		}
		else if (typenm == "QSize") {
			sz = v.toSize();
		}
		else if (typenm == "QString") {
			QStringList parts = v.toString().split(" ");
			if (parts.size() >= 2)
				sz = Size<>(parts[0].toInt(), parts[1].toInt(), 1);
			if (parts.size() == 3)
				sz.zsize(parts[2].toInt());
		}
	}

	void variant2Csy(const QVariant& v, ICoordinateSystem& csy) const;


};
}
}

#endif // INTERNALOBJECTFACTORY_H
