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

#ifndef VERTEXITERATOR_H
#define VERTEXITERATOR_H

namespace geos{
namespace geom {
class LineString;
class Geometry;
class CoordinateSequence;
class Coordinate;
}
}
namespace Ilwis {

const qint32 ENDVERTEX = 100000000;

typedef std::unique_ptr<geos::geom::Geometry> UPGeometry;
class SPFeatureI;

struct VertexCoords{
    VertexCoords(const geos::geom::CoordinateSequence * crds=0, bool isInterior=false) : _crds(crds), _isInterior(isInterior){}
    const geos::geom::CoordinateSequence * _crds;
    bool _isInterior = false;
};
class KERNELSHARED_EXPORT VertexIterator : public std::iterator<std::random_access_iterator_tag, geos::geom::Coordinate>
{
public:
    VertexIterator();
    VertexIterator(geos::geom::Geometry *geom);
    VertexIterator(const UPGeometry &geom);
    VertexIterator(const QString& wkt);
    VertexIterator(const VertexIterator& iter);
    ~VertexIterator();

    VertexIterator& operator=(const VertexIterator& iter);

    VertexIterator& operator++();
    VertexIterator operator++(int n);
    VertexIterator& operator--();
    VertexIterator operator--(int n);
    VertexIterator& operator+=(int n);
    VertexIterator& operator-=(int n);
    VertexIterator operator-(int n) const;
    VertexIterator operator+(int n) const;
    geos::geom::Coordinate& operator[](quint32 n);

    bool operator==(const VertexIterator& iter) const;
    bool operator!=(const VertexIterator& iter) const;
    bool operator<(const VertexIterator& iter) const;
    bool operator>(const VertexIterator& iter) const;
    bool operator<=(const VertexIterator& iter) const;
    bool operator>=(const VertexIterator& iter) const;
    const geos::geom::Coordinate& operator*() const;
    geos::geom::Coordinate& operator*();
    geos::geom::Coordinate* operator->();

    bool nextSubGeometry() const;
    bool isInteriorVertex() const;

private:
    void move(int n);
    void setFromGeometry(geos::geom::Geometry *geom);
    bool compatible(const VertexIterator& iter) const;
    std::vector<VertexCoords> _coordinates;
    std::vector<const geos::geom::Coordinate *> _pointCoordinates;
    bool _nextSubGeometry = false;

    int _index = 0;
    int _partIndex = 0;
    qint32 _linearSize = 0;
    qint32 _linearPosition = 0;
    bool _pointMode = false;
    bool _polygonMode = false;
    bool _hasOwnership = false;
    std::unique_ptr<geos::geom::Geometry> _internalGeom;


    void storeLineString(const geos::geom::LineString *cline, int index, bool isInterior=false);
    bool isAtEnd(const VertexIterator &iter) const;
};

}

inline Ilwis::VertexIterator begin(const std::unique_ptr<geos::geom::Geometry> &geom) {
    return Ilwis::VertexIterator(geom);
}

inline Ilwis::VertexIterator end(const std::unique_ptr<geos::geom::Geometry> &geom) {
    Ilwis::VertexIterator iter(geom);
    iter += Ilwis::ENDVERTEX; //  at the end;
    return iter;
}

inline Ilwis::VertexIterator begin(const Ilwis::SPFeatureI &feature) {
    return Ilwis::VertexIterator(feature->geometry());
}

inline Ilwis::VertexIterator end(const Ilwis::SPFeatureI &feature) {
    Ilwis::VertexIterator iter(feature->geometry());
    iter += Ilwis::ENDVERTEX; //  at the end;
    return iter;
}
inline Ilwis::VertexIterator begin(const Ilwis::VertexIterator &iter) {
    Ilwis::VertexIterator iterNew(iter);
    return iterNew - Ilwis::ENDVERTEX;
}

inline Ilwis::VertexIterator end(const Ilwis::VertexIterator& iter) {
    Ilwis::VertexIterator iterNew(iter);
    iterNew += Ilwis::ENDVERTEX; //  at the end;
    return iterNew;
}

#endif // VERTEXITERATOR_H
