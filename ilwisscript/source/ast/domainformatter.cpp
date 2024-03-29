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

#include "ilwis.h"
#include "symboltable.h"
#include "astnode.h"
#include "idnode.h"
#include "valuerangenode.h"
#include "domainformatter.h"

using namespace Ilwis;

DomainFormatter::DomainFormatter()
{
}

void DomainFormatter::setDomainId(IDNode *node)
{
    _domainId = QSharedPointer<IDNode>(node);
}

void DomainFormatter::setResolution(char *num) {
	QString s(num);
	bool ok;
	_resolution = s.toDouble(&ok);
	if (!ok) {
		_resolution = Ilwis::rUNDEF;
	}
}

double DomainFormatter::resolution() const {
	return _resolution;
}

QString DomainFormatter::nodeType() const
{
    return "dompart";
}
