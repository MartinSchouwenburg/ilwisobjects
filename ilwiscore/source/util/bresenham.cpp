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
#include "location.h"
#include "ilwisdata.h"
#include "size.h"
#include "geos/geom/Coordinate.h"
#include "ilwiscoordinate.h"
#include "box.h"
#include "georeference.h"
#include "geos/geom/Geometry.h"
#include "geos/geom/CoordinateSequence.h"
#include "ilwiscoordinate.h"
#include "feature.h"
#include "vertexiterator.h"
#include "coordinatesystem.h"
#include "bresenham.h"

using namespace Ilwis;

Bresenham::Bresenham(const IGeoReference& grf, const ICoordinateSystem& csy) : _targetGrf(grf), _sourceCsy(csy){

}

std::vector<Pixel> Bresenham::rasterize(const VertexIterator &iterStart, const VertexIterator &iterEnd)
{
    bool convertNeeded = _sourceCsy.isValid() && _sourceCsy != _targetGrf->coordinateSystem();
    VertexIterator iter = iterStart;
    std::vector<Pixel> result;
    Coordinate crd1 = *iter, crd2 ;
    if (convertNeeded){
        crd1 =  _targetGrf->coordinateSystem()->coord2coord(_sourceCsy, crd1);
    }
    quint32 subcount = 0;
    const Size<> sz (_targetGrf->size());
    while( (++iter) != iterEnd ){
        if ( iter.nextSubGeometry()){
            crd1 = *iter;
            ++iter;
            ++subcount;
        }
        crd2 = *iter;
        if (convertNeeded){
            crd2 =  _targetGrf->coordinateSystem()->coord2coord(_sourceCsy, crd2);
        }
        std::vector<Pixel> line  = makePixelLine(crd1, crd2, _valid, sz, subcount);
        if (!_valid)
            return std::vector<Pixel>();
        std::copy(line.begin(), line.end(), std::back_inserter(result));
        crd1 = crd2;
    }
    // remove duplicates
    auto iterUnique = std::unique(result.begin(), result.end());
    result.resize(std::distance(result.begin(),iterUnique));
    return result;
}

bool Bresenham::inBounds(Pixel cur, const Size<> &sz) const {
  return !( cur.x < 0 || cur.y < 0 || cur.x >= sz.xsize() || cur.y >= sz.ysize());
}

std::vector<Pixel> Bresenham::makePixelLine(const Coordinate& crdStart, const Coordinate& crdEnd, bool& valid, const Size <> & sz, quint32 subcount) const
{
    valid = false;
    std::vector<Pixel> result;
    if ( !_targetGrf.isValid()){
        ERROR2(ERR_NO_INITIALIZED_2,TR("target georeference"), "bresenham algorithm");
        return result;
    }

    Pixel begin = _targetGrf->coord2Pixel(crdStart);
    Pixel end = _targetGrf->coord2Pixel(crdEnd);
    if ( !begin.isValid() || !end.isValid()){
        ERROR2(ERR_INVALID_INIT_FOR_2, TR("coordinates"), "bresenham algorithm");
        return result;
    }

    valid = true;

    if ( (begin.x - end.x) == 0) {   // angle = 90
        if ( end.y < begin.y) {
            Pixel temp = end;
            end = begin;
            begin = temp;
        }
        for(double y=0; y < end.y - begin.y; ++y) {
            Pixel cur = Pixel( (long)floor((double)begin.x), (long)floor((double)begin.y + y), subcount);

            if ( inBounds(cur, sz))
                result.push_back(cur);
        }
    }
    else {
        double tan = (double)(begin.y - end.y) / ( begin.x - end.x);
        bool dir = end.y < begin.y;
        if  (dir){
            Pixel temp = end;
            end = begin;
            begin = temp;
        }

        Pixel prev;
        Pixel cur;
        if ( fabs(tan) <= 1) {
            double xdir = end.x - begin.x > 0 ? 1 : -1;
            for(double x=0; x <= fabs(end.x - begin.x); ++x) {
                cur = Pixel( (long)floor((double)begin.x + xdir * x ), (long)floor((double)begin.y + tan * x  * xdir), subcount);\
                if ( cur == prev)
                    continue;
                if ( inBounds(cur, sz))
                    result.push_back(cur);
                prev= cur;
            }

        } else {
            double ydir = end.y - begin.y > 0 ? 1 : -1;
            for(double y=0; y <= fabs(end.y - begin.y); ++y) {
                cur = Pixel( (long)floor((double)begin.x + 1.0/tan * ydir * y), (long)floor((double)begin.y + y), subcount);
                if ( cur == prev)
                    continue;
                if ( inBounds(cur, sz))
                    result.push_back(cur);
                prev = cur;
            }
        }
    }

    return result;
}

