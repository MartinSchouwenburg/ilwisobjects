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

#ifndef GDALCATALOGFILEEXPLORER_H
#define GDALCATALOGFILEEXPLORER_H

namespace Ilwis{
namespace Gdal{
class GdalCatalogFileExplorer : public CatalogExplorer
{
public:
    GdalCatalogFileExplorer(const Ilwis::Resource &resource,const IOOptions& options=IOOptions());
    static Ilwis::CatalogExplorer *create(const Resource &resource,const IOOptions& options=IOOptions());

    bool canUse(const Resource& resource) const;

    std::vector<Ilwis::Resource> loadItems(const IOOptions &options=IOOptions());
    QString provider() const;

    QFileInfo toLocalFile(const QUrl &datasource) const;


    NEW_CATALOGEXPLORER(GdalCatalogFileExplorer);

    CatalogExplorer::ExplorerType explorerType() const;
private:
    void getTypes(const std::multimap<QString, DataFormat> &formats, const QString &ext, IlwisTypes & tp, IlwisTypes & extendedType) const;
};
}
}

#endif // GDALCATALOGFILEEXPLORER_H
