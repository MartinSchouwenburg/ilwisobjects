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

#include <QString>

#include "kernel.h"
#include "geometries.h"
#include "ilwisdata.h"
#include "coordinatesystem.h"
#include "georeference.h"
#include "georefimplementation.h"
#include "simpelgeoreference.h"


using namespace Ilwis;

SimpelGeoReference::SimpelGeoReference(const QString& type) : GeoRefImplementation(type)
{
    clear();
}

SimpelGeoReference::SimpelGeoReference() : GeoRefImplementation("simpel")
{
    clear();
}

GeoRefImplementation *SimpelGeoReference::create()
{
    return new SimpelGeoReference();
}

GeoRefImplementation *SimpelGeoReference::clone()
{
    return create();
}

void SimpelGeoReference::clear() {
    _a11 = _a12 = _a22 = _a21 = rUNDEF;
    _b1 = _b2 = rUNDEF;
    _det = 0;
}

bool SimpelGeoReference::isValid() const {
	return _a11 != rUNDEF && _a12 != rUNDEF && _a22 != rUNDEF && _a21 != rUNDEF &&	_b1 != rUNDEF && _b2 != rUNDEF;
}

Coordinate SimpelGeoReference::pixel2Coord(const Pixeld &pix) const
{
    if (pix.x == iUNDEF || pix.y == iUNDEF)
        return Coordinate();

	if (_a11 == rUNDEF || _a22 == rUNDEF || _a12 == rUNDEF || _a21 == rUNDEF || _b1 == rUNDEF || _b2 == rUNDEF || _det == 0)
		return Coordinate();

    Coordinate c((_a22 * (pix.x - _b1) - _a12 * (pix.y - _b2)) / _det,
                 (-_a21 * (pix.x - _b1) + _a11 * (pix.y - _b2)) / _det );
    return c;
}

Pixeld SimpelGeoReference::coord2Pixel(const Coordinate &crd) const
{
    if (crd.x == rUNDEF || crd.y == rUNDEF)
        return Pixeld();

    double rCol = _a11 * crd.x + _a12 * crd.y + _b1; // - 1;
    double rRow = _a21 * crd.x + _a22 * crd.y + _b2; // - 1;
    Pixeld pix(rCol, rRow);

	if (!isNumericalUndef(crd.z))
		pix.z = crd.z;
    return pix;
}

double SimpelGeoReference::pixelSize() const
{
    if ( _det == 0)
        return rUNDEF;

    return sqrt( 1/ std::abs(_det));
}

std::vector<double> SimpelGeoReference::matrix() const {
    return {_a11,_a21,_a12,_a22};
}

std::vector<double> SimpelGeoReference::support() const {
    return {_b1, _b2};
}

QString SimpelGeoReference::grfType() const {
	return SimpelGeoReference::typeName();
}

QString SimpelGeoReference::typeName()
{
    return "simple";
}

void SimpelGeoReference::copyTo(GeoRefImplementation *impl)
{
    GeoRefImplementation::copyTo(impl);
    SimpelGeoReference *smplgrf = static_cast<SimpelGeoReference *>(impl);
    smplgrf->_a11 = _a11;
    smplgrf->_a12 = _a12;
    smplgrf->_a22 = _a22;
    smplgrf->_a21 = _a21;
    smplgrf->_b1 = _b1;
    smplgrf->_b2 = _b2;
    smplgrf->_det = _det;
}

bool SimpelGeoReference::isCompatible(const IGeoReference &georefOther) const
{
    // TODO: this method should take into account the proper tolerance value,
    // according to the georeference type -- Latlon (2 decimals); otherwise (6 decimals).
    // Add a tolerance (delta) attribute to the georeference class, that should be filled
    // inside its constructor accordingly
    if ( !georefOther->grfType<SimpelGeoReference>())
        return false;
    QSharedPointer<SimpelGeoReference> grfsmpl = georefOther->as<SimpelGeoReference>();
    double delta = EPS6;
    const std::vector<double>& mat = grfsmpl->matrix();
    bool ok = std::abs(mat[0] - _a11) < delta && std::abs(mat[1] - _a21) < delta &&
            std::abs(mat[2] - _a12) < delta && delta && std::abs(mat[3] - _a22) < delta;
    if (!ok)
        return false;
    const std::vector<double>& sup = grfsmpl->support();
    ok = std::abs(sup[0] - _b1) < delta && std::abs(sup[1] - _b2) < delta;

    return ok;
}

bool SimpelGeoReference::isLinear() const
{
  return true;
}
