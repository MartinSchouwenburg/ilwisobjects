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
#include <functional>
#include <future>
#include <memory>
#include "kernel.h"
#include "ilwisdata.h"
#include "ilwisobject.h"
#include "domain.h"
#include "datadefinition.h"
#include "columndefinition.h"
#include "raster.h"
#include "symboltable.h"
#include "operationExpression.h"
#include "operationmetadata.h"
#include "commandhandler.h"
#include "operation.h"
#include "tranquilizer.h"
#include "operationoverloads.h"
#include "testoperation.h"

using namespace Ilwis;
using namespace BaseOperations;

REGISTER_OPERATION(TestOperation)

Ilwis::OperationImplementation *TestOperation::create(quint64 metaid, const Ilwis::OperationExpression &expr)
{
    return new TestOperation(metaid, expr);
}

TestOperation::TestOperation()
{
}

TestOperation::TestOperation(quint64 metaid, const Ilwis::OperationExpression &expr) : OperationImplementation(metaid, expr)
{

}

bool TestOperation::execute(ExecutionContext *ctx, SymbolTable &symTable)
{
    if (_prepState == sNOTPREPARED)
        if((_prepState = prepare(ctx, symTable)) != sPREPARED)
            return false;

    IRasterCoverage newr1 = _raster1 + 1;
    IRasterCoverage newr2 = _raster2 / 2;

    QVariant value1;
    value1.setValue<IRasterCoverage>(newr1);
    ctx->setOutput(symTable, value1, newr1->name(), itRASTER, newr1->resource());

    QVariant value2;
    value2.setValue<IRasterCoverage>(newr2);
    ctx->addOutput(symTable, value2, newr2->name(), itRASTER, newr2->resource());


    return true;
}

Ilwis::OperationImplementation::State TestOperation::prepare(ExecutionContext *ctx, const SymbolTable &)
{

    QString inname1 = _expression.input<QString>(0);
    QString inname2 = _expression.input<QString>(1);

    _raster1.prepare(inname1);
    _raster2.prepare(inname2);

    return sPREPARED;
}

quint64 TestOperation::createMetadata()
{
    OperationResource operation({"ilwis://operations/testoperation"});
    operation.setSyntax("testoperation(raster1, raster2)");
    operation.setDescription(TR("dummy/test operation to test certain internal workings of the handling of operations"));
    operation.setInParameterCount({2});
    operation.addInParameter(0,itRASTER , TR("input raster1"));
    operation.addInParameter(1,itRASTER, TR("input raster2"));
    operation.setOutParameterCount({2});
    operation.addOutParameter(0,itRASTER , TR("output1"));
    operation.addOutParameter(1,itRASTER , TR("output2"));
    operation.setKeywords("test");

    operation.checkAlternateDefinition();
    mastercatalog()->addItems({operation});
    return operation.id();

}




