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

#include "coverage.h"
#include "errorobject.h"
#include "astnode.h"
#include "symboltable.h"
#include "geos/geom/Coordinate.h"
#include "geos/geom/Geometry.h"
#include "ilwiscoordinate.h"
#include "operationnodescript.h"
#include "expressionnode.h"
#include "featurecoverage.h"
#include "feature.h"
#include "selectnode.h"

using namespace Ilwis;

SelectNode::SelectNode()
{
}

void SelectNode::setInput(const QString &input)
{
    if ( input.indexOf("url|") == 0 ){

        _inputId = "\"" + QString(input).remove("\"") + "\"";
        _isUrl = true;
    }
    else
        _inputId = input.mid(3);
}
QString SelectNode::inputId() const
{
    return _inputId;
}

bool SelectNode::evaluate(SymbolTable &symbols, int scope, ExecutionContext *ctx)
{
    ctx->_additionalInfo[IMPLICITPARMATER0] = _inputId;
    ctx->_useAdditionalParameters = true;
    if(!_expression->evaluate(symbols, scope, ctx))
        return false;

    _value = _expression->value();

    return true;
}

void SelectNode::setExpression(ExpressionNode *n)
{
    _expression = QSharedPointer<ExpressionNode>(n);
}





