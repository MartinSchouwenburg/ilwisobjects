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
#include <QSharedPointer>
#include "kernel.h"
#include "identity.h"
#include "ilwisdata.h"
#include "ilwisobject.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "thematicitem.h"
#include "itemrange.h"
#include "identifieritem.h"
#include "identifierrange.h"

using namespace Ilwis;

inline bool operator == (const Ilwis::ThematicItem& item1, const Ilwis::ThematicItem& item2) {
    return item1.name() == item2.name();
}

ThematicItem::ThematicItem()
{
    code(sUNDEF);
    description(sUNDEF);
}

ThematicItem::ThematicItem(const QStringList& parts, quint32 rawvalue) : NamedIdentifier(sUNDEF, rawvalue) {
    if ( parts.size() > 0) {
        setName(parts[0]);
        if ( parts.size() > 1)
            code(parts[1]);
        if ( parts.size() == 3) {
            QString desc = parts[2];
            desc.remove("\"");
            description(desc);
        }
    }
}

ThematicItem::ThematicItem(const QString itemname, const QString& itemcode, const QString& itemdesc){
    setName(itemname);
    code(itemcode);
    description(itemdesc);
}

QString ThematicItem::description() const
{
    return _description;
}

QString ThematicItem::code() const
{
    return _code;
}

void ThematicItem::description(const QString &desc)
{
    _description = desc;
}

void ThematicItem::code(const QString &code)
{
    _code = code;
}

DomainItem *ThematicItem::clone() const
{

    ThematicItem *item = new ThematicItem(name(), _code, _description);
    item->_raw = _raw;

    return item;
}

IlwisTypes ThematicItem::valueTypeS()
{
    return itTHEMATICITEM;
}

IlwisTypes ThematicItem::valueType() const
{
    return valueTypeS();
}

ItemRange *ThematicItem::createRange()
{
    return new ThematicRange();
}





