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

#ifndef STREAMRASTERDATAINTERFACE_H
#define STREAMRASTERDATAINTERFACE_H

namespace Ilwis {
namespace Stream {



class RasterSerializerV1 : public CoverageSerializerV1
{
public:
    RasterSerializerV1(QDataStream& stream, const QString &version);

    bool store(IlwisObject *obj, const IOOptions& options = IOOptions());
    bool storeData(IlwisObject *obj, const IOOptions& options = IOOptions()) override ;
    bool loadMetaData(IlwisObject*obj, const IOOptions & options);
    bool loadData(IlwisObject *data, const IOOptions &options);
//    quint32 loadGridBlock(IlwisObject *data, quint32 block, QByteArray& blockdata, const RawConverter& converter, const IOOptions &options);
    static VersionedSerializer *create(QDataStream &stream, const QString &version);

private:


};
}
}

#endif // STREAMRASTERDATAINTERFACE_H
