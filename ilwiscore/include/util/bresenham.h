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

#ifndef BRESENHAM_H
#define BRESENHAM_H
#include "kernel_global.h"

namespace Ilwis {

class VertexIterator;

class KERNELSHARED_EXPORT Bresenham
{
public:
    Bresenham(const IGeoReference &grf, const Ilwis::ICoordinateSystem &csy=ICoordinateSystem());
    std::vector<Pixel> rasterize(const VertexIterator& iterStart, const VertexIterator& iterEnd);

private:
    std::vector<Pixel> makePixelLine(const Ilwis::Coordinate &crdStart, const Ilwis::Coordinate &crdEnd, bool &valid, const Size <> & sz, quint32 subcount) const;
    bool inBounds(Pixel cur, const Size <> & sz) const;
    IGeoReference _targetGrf;
    ICoordinateSystem _sourceCsy;
    bool _valid = false;
};
}

#endif // BRESENHAM_H
