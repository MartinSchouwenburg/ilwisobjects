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

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "raster.h"
#include "symboltable.h"
#include "astnode.h"
#include "idnode.h"
#include "domainformatter.h"
#include "operationnodescript.h"
#include "expressionnode.h"
#include "symboltable.h"
#include "formatter.h"
#include "formatters.h"
#include "scriptnode.h"
#include "table.h"
#include "basetable.h"
#include "flattable.h"
#include "featurecoverage.h"
#include "feature.h"
#include "numericrange.h"
#include "numericdomain.h"
#include "connectorinterface.h"
#include "factory.h"
#include "abstractfactory.h"
#include "connectorfactory.h"
#include "catalog.h"
#include "mastercatalog.h"
#include "ilwiscontext.h"
#include "juliantime.h"
#include "combinationmatrix.h"
#include "selectnode.h"
#include "selectornode.h"
#include "outparametersnode.h"
#include "dataformat.h"
#include "representation.h"
#include "operationhelper.h"
#include "assignmentnode.h"

using namespace Ilwis;

AssignmentNode::AssignmentNode() : _defintion(false)
{
}

bool AssignmentNode::isDefinition() const
{
    return _defintion;
}

void AssignmentNode::setDefintion(bool yesno)
{
    _defintion= yesno;
}

void AssignmentNode::setExpression(ASTNode *node)
{
    _expression =QSharedPointer<ASTNode>(node);
}

QString AssignmentNode::nodeType() const
{
    return "assignment";
}

IIlwisObject AssignmentNode::getObject(const Symbol& sym) const {
    IlwisTypes tp = sym._type;
    if ( tp & itRASTER)
        return sym._var.value<Ilwis::IRasterCoverage>().as<IlwisObject>();
    if ( tp & itFEATURE)
        return sym._var.value<Ilwis::IFeatureCoverage>().as<IlwisObject>();
    if (hasType(tp, itTABLE | itCOLUMN)) {
        auto obj = sym._var.value<Ilwis::ITable>().as<IlwisObject>();
        if (obj.isValid())
            return obj;
    }
    if (hasType(tp, itFLATTABLE))
        return sym._var.value<Ilwis::IFlatTable>().as<IlwisObject>();
    if ( hasType(tp , itDOMAIN))
        return sym._var.value<Ilwis::IDomain>().as<IlwisObject>();
	if (hasType(tp, itREPRESENTATION))
		return sym._var.value<Ilwis::IRepresentation>().as<IlwisObject>();
    if ( hasType(tp , itGEOREF))
        return sym._var.value<Ilwis::IGeoReference>().as<IlwisObject>();
    if ( hasType(tp , itCOORDSYSTEM))
        return sym._var.value<Ilwis::ICoordinateSystem>().as<IlwisObject>();
    if ( hasType(tp , itCOMBINATIONMATRIX))
        return sym._var.value<Ilwis::ICombinationMatrix>().as<IlwisObject>();
    return IIlwisObject();

}
void AssignmentNode::setResolution(IRasterCoverage& raster, QSharedPointer<ASTNode>& node) const {
	for (int i = 0; i < node->noOfChilderen(); ++i) {
		auto data = node->child(i).data();
		if (data->nodeType() == "dompart" && raster->datadef().domain()->ilwisType() == itNUMERICDOMAIN) {
			DomainFormatter *formatter = static_cast<DomainFormatter *>(data);
			double res = formatter->resolution();
			if (res != rUNDEF) {
				NumericRange *rng = raster->datadefRef().range()->as<NumericRange>();
				rng->resolution(res);
				for (int z = 0; z < raster->size().zsize(); ++z) {
					NumericRange *rng =  raster->datadefRef(z).range()->as<NumericRange>();
					rng->resolution(res);
				}
			}
		}
	}
}

void AssignmentNode::getFormat(QSharedPointer<ASTNode>& node, QString& format, QString& fnamespace) const {
	for (int i = 0; i < node->noOfChilderen(); ++i) {
		auto data = node->child(i).data();
		if (data->nodeType() == "Formatter") {
			Formatter *fnode = static_cast<Formatter *>(data);
			format = fnode->format();
			fnamespace = fnode->fnamespace();

			if (format == "" || format == sUNDEF) {
				Formatter *fnode = ScriptNode::activeFormat(itRASTER);
				if (fnode) {
					format = fnode->format();
					fnamespace = fnode->fnamespace();
				}
			}
		}
	}
}

void AssignmentNode::store2Format(QSharedPointer<ASTNode>& node, const Symbol& sym, const QString& result) {
    QString format, provider;
    getFormat(node, format, provider);
    if ( format != "" && format != sUNDEF) {
        Ilwis::IIlwisObject object = getObject(sym);
        if ( object.isValid()){
            bool wasAnonymous = object->isAnonymous(); // if object is anonymous it will get a name due this method; this means it will now appear in the mastercatalog
            // as (previous) anonymous objects are not in the mastercatalog ( though they are registered)
            QString name = result;
            QUrl url;
            QUrl normalizedUrl;
            if ( result.indexOf(":/") != -1 && result.indexOf("//") != -1) {// is already an url, than we figure out its name from the url
                url = result;
                name = result.mid(result.lastIndexOf("/") + 1);
            }
            else
                // no path information so we create our own path, the name has no path information so can be used as is
                if ( provider != "stream"){ // stream goes to the internal if nothing has ben defined and that is default.
                    url = context()->workingCatalog()->resource().url().toString() + "/" + result;
                }else {
                    url = context()->persistentInternalCatalog().toString() + "/" + result;
                    normalizedUrl = INTERNAL_CATALOG + "/" + result;
                }
            object->name(name);
            // we reuse an existing connector if it is of the same provider; it will than inherit/use properties of the "old" connector
            if ( object->provider() != provider)
                object->connectTo(url, format, provider, Ilwis::IlwisObject::cmOUTPUT);
            object->createTime(Ilwis::Time::now());
            if ( wasAnonymous)
                mastercatalog()->addItems({object->resource(IlwisObject::cmOUTPUT | IlwisObject::cmEXTENDED)});

            IOOptions opt({"storemode",Ilwis::IlwisObject::smMETADATA | Ilwis::IlwisObject::smBINARYDATA});
            opt << IOOptions::Option{"format",format};
            object->store(opt);
        }else {
            kernel()->issues()->log(QString(TR("Couldn't retrieve symbol from symbol table, object will not be stored")));
        }

    }
}

void createCatalog(const IRasterCoverage& raster){
    Resource resCatalog = raster->resource();
    resCatalog.newId();
    resCatalog.name(raster->name());
    resCatalog.createTime(Time::now());
    resCatalog.modifiedTime(Time::now());
    resCatalog.setIlwisType(itCATALOG);
    resCatalog.setExtendedType(resCatalog.extendedType() | itRASTER);
    mastercatalog()->addItems({resCatalog});
    std::vector<Resource> bands;
    RasterStackDefinition defs = raster->stackDefinition();
    bool namedLayers = !hasType(raster->stackDefinition().domain()->ilwisType(), itNUMBER);
    for(quint32 band=0; band < raster->size().zsize(); ++band){
        Resource resBand = raster->resource();
        resBand.newId();
        resBand.createTime(Time::now());
        resBand.modifiedTime(Time::now());
        QUrl newUrl = resBand.url().toString();
        QString newName = resBand.name() + "_" + defs.index(band);
        if ( namedLayers)
            newName = defs.index(band);
        newName.remove(".ilwis");
        resBand.setUrl(newUrl.toString() + "/" + newName);
        resBand.code("band="+QString::number(band));
        resBand.setExtendedType(resBand.extendedType() & ~itCATALOG);
        bands.push_back(resBand);
    }
    mastercatalog()->addItems(bands);
}

QString AssignmentNode::addPossibleExtension(QSharedPointer<ASTNode> &specifier, QString result, IlwisTypes tp)
{
    result = OperationHelper::unquote(result);
    if (!specifier.isNull()){
        QString format, provider;
        getFormat(specifier, format, provider);
        QVariantList extensions = Ilwis::DataFormat::getFormatProperties(DataFormat::fpEXTENSION,tp, provider, format);
        if ( extensions.size() > 0 && result.indexOf("." + extensions[0].toString()) == -1){
            result += "." + extensions[0].toString();

        }
    }
    return result;
}

bool AssignmentNode::evaluate(SymbolTable& symbols, int scope, ExecutionContext *ctx)
{
    if ( _expression.isNull())
        return false;

    try{
        bool ok = _expression->evaluate(symbols, scope, ctx);
        if ( ok) {
            // we save the additional info  as we might need it but for the rest clear
            // the results as the result of the assignment node is a newly filled ctx
            auto additionalInfo = ctx->_additionalInfo;
            ctx->clear(true);

            NodeValue val = _expression->value();
            for(int i = 0; i < val.size(); ++i) {
                Symbol sym = symbols.getSymbol(val.id(i),SymbolTable::gaREMOVEIFANON);
                IlwisTypes tp = sym.isValid() ? sym._type : itUNKNOWN;
                QString result = _outParms->id(i);
                QSharedPointer<ASTNode> specifier = _outParms->specifier(_outParms->id(i));
                if (  hasType(tp, itILWISOBJECT)){
                    result = addPossibleExtension(specifier, result, tp);
                }
                if (  hasType(tp, itILWISOBJECT | itCOLUMN)) {
                    if ( hasType(tp, itRASTER)) {
                        IRasterCoverage source =  sym._var.value<IRasterCoverage>();
                        if (source.isValid() && source->size().zsize() > 1) {
                            source->extendedType(source->extendedType() | itCATALOG);
                        }
                        ok &= copyObject<RasterCoverage>(sym, result,symbols);
                        IRasterCoverage resultGC = symbols.getValue<IRasterCoverage>(result);
                        if ( resultGC.isValid() && resultGC->size().zsize() > 1){
                            createCatalog(resultGC);
                        }
                        if ( !specifier.isNull())
                            setResolution(resultGC, specifier);

                    }
                    else if (hasType(tp, itFEATURE))
                        ok &= copyObject<FeatureCoverage>(sym, result,symbols);
                    else if (hasType(tp, itCOORDSYSTEM))
                        ok &= copyObject<CoordinateSystem>(sym, result,symbols);
                    else if ( hasType(tp, itDOMAIN)){
                        ok &= copyObject<Domain>(sym, result,symbols);
                   } if (hasType(tp, itREPRESENTATION)) {
					   ok &= copyObject<Representation>(sym, result, symbols);
				   } else if ( hasType(tp, itCOMBINATIONMATRIX)){
                       ok &= copyObject<CombinationMatrix>(sym, result,symbols);
                    } else if ( hasType(tp, itGEOREF)){
                        ok &= copyObject<GeoReference>(sym, result,symbols);
                    } else if (hasType(tp, itTABLE | itCOLUMN)){
                        // try generic type first (Table); if failed try specific type (FlatTable)
                        ok &= copyObject<Table>(sym, result,symbols,false, additionalInfo);
                        if (!ok && tp == itFLATTABLE)
                            ok &= copyObject<FlatTable>(sym, result,symbols,false, additionalInfo);
                        QSharedPointer<Selector> selector = _outParms->selector(result);
                        if (!selector.isNull()){
                            QString varName = selector->variable();
                            ITable source =  sym._var.value<ITable>();
                            QString oldColName = additionalInfo[source->name()].toString();
                            QVariant newT= symbols.getValue(result);
                            ITable newTable = newT.value<ITable>();
                            ColumnDefinition& coldef = newTable->columndefinitionRef(oldColName);
                            if ( coldef.isValid()){
                                coldef.name(varName);
                            }
                        }
                    }

                    if(!ok) {
                        throw ErrorObject(QString(TR(ERR_OPERATION_FAILID1).arg("assignment")));
                    }
                    if ( !specifier.isNull()) {
                        store2Format(specifier, sym, result);

                    }

                    ctx->_results.push_back(result);

                } else {
                    tp = sym.isValid() ? sym._type : itUNKNOWN;
                    if ( tp == itUNKNOWN) {
                        tp = Domain::ilwType(val);
                    }
                    result.remove(".ilwis"); // dont need that here
                    ctx->addOutput(symbols,_expression->value(),result, tp, Resource());
                }
                //ctx->addOutput(symbols,_expression->value(),result, tp, Resource());

        }
    }
    return ok;
} catch(const ErrorObject&){

}

return false;
}

void AssignmentNode::addOutputs(OutParametersNode *p)
{
    _outParms.reset(p);
}

void AssignmentNode::setOutId(IDNode *idnode)
{
    _outParms.reset(new OutParametersNode());
    _outParms->addResult(idnode);

}


