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
#include "operationmetadata.h"
#include "symboltable.h"
#include "geos/geom/Coordinate.h"
#include "location.h"
#include "ilwiscoordinate.h"
#include "box.h"
#include "modeller/workflownode.h"
#include "operationExpression.h"
#include "modeller/workflow.h"
#include "modeller/applicationmodel.h"
#include "modeller/analysispattern.h"
#include "modeller/model.h"

using namespace Ilwis;

AnalysisPattern::AnalysisPattern()
{

}

AnalysisPattern::AnalysisPattern(const QString &name, const QString &description) : Identity(name,i64UNDEF, description)
{

}

void AnalysisPattern::store(QDataStream &stream)
{
    Identity::store(stream);
}

void AnalysisPattern::loadMetadata(QDataStream &stream)
{
    Identity::load(stream)    ;
}

void AnalysisPattern::loadData(QDataStream &stream)
{
    //TODO
}

void AnalysisPattern::attachedModel(quint64 modelid)
{
    _modelId = modelid;
}

void AnalysisPattern::addData(const QString& key, const QVariant& var) {

}

QVariant AnalysisPattern::data(const QString& key) const {
	return QVariant();
}

IModel AnalysisPattern::attachedModel()
{
    if ( !_attachedModel.isValid())
        _attachedModel.prepare(_modelId);
    return _attachedModel;
}
