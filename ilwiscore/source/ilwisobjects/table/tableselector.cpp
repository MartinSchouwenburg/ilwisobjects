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
#include "ilwisdata.h"
#include "domain.h"
#include "domainitem.h"
#include "itemdomain.h"
#include "range.h"
#include "identifieritem.h"
#include "identifierrange.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "logicalexpressionparser.h"
#include "connectorinterface.h"
#include "basetable.h"
#include "flattable.h"
#include "tableselector.h"

using namespace Ilwis;

TableSelector::TableSelector()
{
}

std::vector<quint32> TableSelector::select(const Table* table, const QString &conditions)
{
    LogicalExpressionParser parser(conditions);
    if ( !parser.isValid()) {
        return std::vector<quint32>();
    }
    std::vector<bool> status(table->recordCount(),false);
    for(auto part : parser.parts()) {
        std::vector<QVariant> data = table->column(part.field());
        if (data.size() == 0) {
            ERROR2(ERR_ILLEGAL_VALUE_2,TR("expression"), conditions);
            return std::vector<quint32>();
        }
        const ColumnDefinition& coldef = const_cast<Table *>(table)->columndefinitionRef(part.field());

        auto iter = status.begin();
        IlwisTypes vt = coldef.datadef().domain()->valueType();
        for(const QVariant& var : data) {
            if ( hasType(vt, itNUMBER)){
                if ( hasType(vt, itDATETIME))
                    numericCase(part, (double)var.value<Ilwis::Time>(), iter);
                else
                    numericCase(part, var.toDouble(), iter);
            }
            else if ( hasType(vt, itSTRING )){
                stringCase(part, coldef, var, iter);
            }
            ++iter;
        }

    }
    std::vector<quint32> result;
    for(int i=0; i < status.size(); ++i)
        if(status[i])
            result.push_back(i);

    return result;
}
void TableSelector::stringCase(const LogicalExpressionPart& part, const ColumnDefinition& coldef, const QVariant& var, std::vector<bool>::iterator& iter) {
    QString text = part.value();
    QString fieldtxt = var.toString();
    if ( coldef.datadef().domain<>()->valueType() == itTHEMATICITEM){
        quint32 raw = var.toUInt();
        INamedIdDomain domainid = coldef.datadef().domain<>().as<NamedIdDomain>();
        SPDomainItem item = domainid->item(raw);
        fieldtxt = item->name();
    }
    LogicalOperator lconnector =  part.logicalConnector();
    switch(part.condition()){
    case loEQ:{
        switch(lconnector){
        case loNONE:
            *iter = fieldtxt == text;break;
        case loOR:
            *iter = *iter || fieldtxt == text;break;
        case loAND:
            *iter = *iter && fieldtxt == text;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loNEQ:{
        switch(lconnector){
        case loNONE:
            *iter = fieldtxt != text;break;
        case loOR:
            *iter = *iter || fieldtxt != text;break;
        case loAND:
            *iter = *iter && fieldtxt != text;break;
        default:
            *iter = false;break;
        }
        break;
    }
    default:
        *iter = false;
    }
}


void TableSelector::numericCase(const LogicalExpressionPart& part, double val1, std::vector<bool>::iterator& iter) {
    double val2 = rUNDEF;
    if ( part.value() != "?")
        val2 = part.value().toDouble();
    if ( isNumericalUndef(val1))
        val1 = rUNDEF;

    LogicalOperator lconnector =  part.logicalConnector();
    switch(part.condition()){
    case loEQ:{
        switch(lconnector){
        case loNONE:
            *iter = val1 == val2;break;
        case loOR:
            *iter = *iter || val1 == val2;break;
        case loAND:
            *iter = *iter && val1 == val2;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loNEQ:{
        switch(lconnector){
        case loNONE:
            *iter = val1 != val2;break;
        case loOR:
            *iter = *iter || val1 != val2;break;
        case loAND:
            *iter = *iter && val1 != val2;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loLESS:{
        switch(lconnector){
        case loNONE:
            *iter = (val1 < val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loOR:
            *iter = (*iter || val1 < val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loAND:
            *iter = (*iter && val1 < val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loLESSEQ:{
        switch(lconnector){
        case loNONE:
            *iter = (val1 <= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loOR:
            *iter = (*iter || val1 <= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loAND:
            *iter = (*iter && val1 <= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loGREATEREQ:{
        switch(lconnector){
        case loNONE:
            *iter = (val1 >= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loOR:
            *iter = (*iter || val1 >= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loAND:
            *iter = (*iter && val1 >= val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        default:
            *iter = false;break;
        }
        break;
    }
    case loGREATER:{
        switch(lconnector){
        case loNONE:
            *iter = (val1 > val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loOR:
            *iter = (*iter || val1 > val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        case loAND:
            *iter = (*iter && val1 > val2) && val1 !=rUNDEF && val2 != rUNDEF;break;
        default:
            *iter = false;break;
        }
        break;
    }
    default:
        *iter = false;break;

    }
}
