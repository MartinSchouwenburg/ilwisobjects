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

#include <QUrl>
#include "kernel.h"
#include "connectorinterface.h"
#include "ilwisobject.h"
#include "ilwisdata.h"
#include "numericrange.h"
#include "numericdomain.h"

using namespace Ilwis;

NumericDomain::NumericDomain()
{
    range(new NumericRange(-1e300, 1e300));
}

NumericDomain::NumericDomain(const Resource& resource) : Domain(resource) {
    if ( hasType(resource.extendedType(), itINT8))
        range(new NumericRange(-127, 128,1));
    else if (hasType(resource.extendedType(), itUINT8)){
        range(new NumericRange(0, 255,1));
    } else if (hasType(resource.extendedType(), itINT16)){
        range(new NumericRange(-32768, 32768,1));
    } else if (hasType(resource.extendedType(), itUINT16)){
        range(new NumericRange(0, 65536,1));
    } else if (hasType(resource.extendedType(), itINT32)){
        range(new NumericRange(-2147483648.0, 2147483648.0,1));
    }else if (hasType(resource.extendedType(), itUINT32)){
        range(new NumericRange(0, 4294967296,1));
    }else if (hasType(resource.extendedType(), itINT64)){
        range(new NumericRange(-9223372036854775807LL, 9223372036854775807LL,1));
    }else if (hasType(resource.extendedType(), itINT64)){
        range(new NumericRange(0, 18446744073709551615ULL,1));
    }else if (hasType(resource.extendedType(), itFLOAT)){
        range(new NumericRange(-1e38, 1e38));
    }else {
        range(new NumericRange(-1e300, 1e300));
    }
}

NumericDomain::NumericDomain(NumericRange *r)
{
    range(r);
}

void NumericDomain::range(Range *vr)
{
    if ( isReadOnly())
        return;
    changed(true);
    if ( hasType(vr->valueType(), itNUMBER) == false)
        return;
    if ( parent().isValid()) {
        parent()->range<NumericRange>()->contains(static_cast<NumericRange *>(vr));
    }
    _range = QSharedPointer<NumericRange>(static_cast<NumericRange *>(vr));
}

IlwisTypes NumericDomain::valueType() const
{
    if ( !_range.isNull())
        return _range->valueType();

    return itUNKNOWN;
}

IlwisTypes NumericDomain::ilwisType() const
{
    return itNUMERICDOMAIN;
}

void NumericDomain::setParent(const IDomain &dm)
{
    if ( isReadOnly())
        return;
    changed(true);

    if ( _range.isNull()) {
        return;
    }
    if ( dm->ilwisType() != itNUMERICDOMAIN || hasType(dm->valueType(), itNUMBER) == false)
        return;
    SPNumericRange numrange = dm->range<NumericRange>();
    if ( !numrange->contains(_range))
        return;

    Domain::setParent(dm);
}

IlwisObject *NumericDomain::clone()
{
    NumericDomain * numdom = new NumericDomain();
    copyTo(numdom);
    return numdom;
}

void NumericDomain::copyTo(IlwisObject *obj){
    Domain::copyTo(obj);
    NumericDomain *numdom = static_cast<NumericDomain *>(obj);
    numdom->_range.reset(static_cast<NumericRange *>(_range->clone()));
}

QString NumericDomain::standardNumericDomainName(double vmin, double vmax, double step)
{
    QString domName="value";
    bool isInt = std::abs(vmin - (int)vmin) == 0 && std::abs(vmax - (int)vmax) == 0;
    if ( step - (int)step != 0)
        isInt = false;
    if ( isInt) {
        if ( vmin >= 0 && vmax < 256)
            domName = "image";
        else  if ( vmin >= 0 && vmax < 65536)
            domName = "image16";
        else if ( vmax >= 0) {
            domName = "count";
        } else
            domName = "Integer";
    } else {
        if ( vmin >= -1 && vmax <= 1)
            domName = "min1to1" ;
        else if ( vmin >= 0 && vmax <=1)
            domName = "nilto1";
    }
    return domName;
}

SPRange NumericDomain::getRange() const
{
    return _range;
}

QVariant NumericDomain::impliedValue(const QVariant &v) const
{
    if ( !_range.isNull()){
        return _range->impliedValue(v);
    }
    ERROR2(ERR_INVALID_PROPERTY_FOR_2,"range", this->name());
    return QVariant();
}

Domain::Containement NumericDomain::contains(const QVariant &value) const
{
    if ( !_range.isNull()) {
        if ( !_range.isNull() && _range->contains(value))
            return Domain::cSELF;
        if (parent().isValid() && !isStrict())
            if (parent()->contains(value) == Domain::cSELF)
                return Domain::cPARENT;
    }
    return Domain::cNONE;
}

bool NumericDomain::isCompatibleWith(const IlwisObject *obj, bool strict) const {
    if ( !obj || !obj->isValid())
        return false;
    if(obj->ilwisType() != itNUMERICDOMAIN)
        return false;
    if (strict) {
        const NumericDomain * dm2 = static_cast<const NumericDomain*>(obj);
        if (!_range.isNull() && !dm2->_range.isNull())
            return *_range == *dm2->_range;
    }
    return true;
}

bool NumericDomain::isOrdered() const
{
    return true;
}







