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
#include <QStandardPaths>
#include <QDir>
#include "kernel.h"
#include "ilwisdata.h"
#include "domain.h"
#include "catalog.h"
#include "connectorinterface.h"
#include "symboltable.h"
#include "dataformat.h"
#include "mastercatalog.h"
#include "ilwiscontext.h"
#include "operationhelper.h"
#include "operationExpression.h"

using namespace Ilwis;

Parameter::Parameter() : _key(sUNDEF), _value(sUNDEF), _type(itUNKNOWN), _domain(sUNDEF) {
}

Parameter::Parameter(const QString &key, const QString &value, IlwisTypes tp, const SymbolTable &symtab) :
    Identity(key),
    _value(value),
    _domain(sUNDEF)
{
    _type = tp;
    if ( _type == itUNKNOWN)
        _type = Parameter::determineType(value, symtab);
}

Parameter::Parameter(const QString &value, IlwisTypes tp, const SymbolTable &symtab) : _domain(sUNDEF)
{
    _value = value;
    _type = tp;
    if ( _type == itUNKNOWN)
        _type = Parameter::determineType(_value, symtab);
}

Ilwis::Parameter::~Parameter()
{
}

QString Parameter::value() const
{
    return OperationHelper::unquote(_value);
}

QString Parameter::domain() const
{
    return _domain;
}

void Parameter::domain(const QString &dom)
{
    _domain = dom;
}

IlwisTypes Parameter::valuetype() const
{
    return _type;
}

bool Parameter::isEqual(const Parameter &parm) const
{
    return parm.name() == name() && parm.value() == _value;
}

bool Parameter::isValid() const
{
    return !_value.isEmpty();
}

Parameter::PathType Parameter::pathType() const
{
    if ( _value.indexOf("http://") == 0 || _value.indexOf("https://") == 0){
        return ptREMOTE;
    }
    if ( _value.indexOf("file://") == 0){
        return ptLOCALOBJECT;
    }
    if ( _value.indexOf("ilwis://") == 0){
        return ptLOCALOBJECT;
    }
    if ( _value.indexOf("?") == 0)
        return ptUNDEFINED;

    if ( hasType(_type, (itSTRING | itNUMBER | itBOOL)))
        return ptIRRELEVANT;

    return ptNONE;
}

IlwisTypes Parameter::determineType(const QString& value, const SymbolTable &symtab) {
    bool ok;
    value.toDouble(&ok);
    if ( ok)
        return itNUMBER;

    kernel()->issues()->silent(true);  // suppress error messages during probe of value

    QString unquotedValue = OperationHelper::unquote(value);
    IlwisTypes tp = IlwisObject::findType(unquotedValue);
    if ( value == "\"?\"" || value == "?")
        tp = itANY;

    if ( tp != itUNKNOWN) {
        kernel()->issues()->silent(false);
        return tp;
    }

    Symbol sym = symtab.getSymbol(unquotedValue);
    if ( sym.isValid() && sym._type != itUNKNOWN) {
        kernel()->issues()->silent(false);
        return sym._type;
    }

    QString s = context()->workingCatalog()->resolve(unquotedValue);
    IlwisTypes type = IlwisObject::findType(s) ;
    if ( type != itUNKNOWN) {
        kernel()->issues()->silent(false);
        return type;
    }

    quint64 id = IlwisObject::internalname2id(unquotedValue);
    if ( id != i64UNDEF){
        ESPIlwisObject obj =  mastercatalog()->get(id);
        if ( obj.get() != 0) {
            kernel()->issues()->silent(false);
            return obj->ilwisType();
        }
    }
    tp = Domain::ilwType(unquotedValue);
    kernel()->issues()->silent(false);
    return tp == itUNKNOWN ? itSTRING : tp;
}



//----------------------------------------

OperationExpression::OperationExpression()
{
}

Ilwis::OperationExpression::~OperationExpression()
{
}

OperationExpression::OperationExpression(const QString &e, const SymbolTable &symtab)
{
    setExpression(e, symtab);
}

void OperationExpression::setExpression(const QString &e, const SymbolTable &symtab) {
    _name = "";
    _inParameters.clear();
    _outParameters.clear();
    _inParametersMap.clear();
    _type = otFunction;
    QString dummy = e;
    int index1 = e.indexOf(" ");
    int index2 = e.indexOf("=");
    int index3 = e.indexOf("[");
    int index4 = e.lastIndexOf(")");
    if ( index4 > index3)
        index3 = -1;
    bool isCommand = index1 != -1 && ( index1 < index2 || index2 == -1);
    if ( isCommand) {
        _type = otCommand;
        for(int i = 0; i < index1; ++i){
            if ( !(e[i].isDigit() || e[i].isLetter() || e[i] == '-')){
                _type = otFunction;
                break;
            }
        }
    }
    else if ( index3 != -1)
        _type = otSelection;

    if ( _type == otFunction) {
        parseFunctionExpression(e, symtab);
    } else if ( _type == otCommand) {
        parseCommandExpression(e, symtab);
    } else if ( _type == otSelection) {
        parseSelectors(e, symtab);
    }
}

void OperationExpression::parseCommandExpression(const QString &e, const SymbolTable &symtab) {
    if ( e.left(6) == "script"){ // special case , all after tyhe script statement is the script text
        _name = "script";
        QString rest = e.mid(7).trimmed();
        _inParameters.push_back(Parameter(rest, itSTRING, symtab));
        return;
    }
    int blockCount = 0;
    int quoteCount = 0;
    int count = 0;
    QList<int> indexes;
    foreach(const QChar& cu, e) {
        char c = cu.toLatin1(); // eessions are not internatiolized, so its allowed
        if ( c == '(' && quoteCount == 0)
            blockCount++;
        if ( c == ')' && quoteCount == 0)
            blockCount--;
        if ( c == '"' && quoteCount == 0)
            quoteCount++;
        else if ( c == '"' && quoteCount != 0)
            quoteCount--;

        if ( c == ' ' && blockCount == 0 && quoteCount == 0)
            indexes.push_back(count++);
        ++count;
    }
    indexes.push_back(count - 1);
    int current = 0;
    foreach(int index, indexes) {
        QString part = e.mid(current, index - current) ;
        part = part.trimmed();
        if ( current == 0)
            _name = part;
        else
            _inParameters.push_back(Parameter(part, itUNKNOWN, symtab));
        current = index;
    }
}

void  OperationExpression::parseSelectors(const QString& e, const SymbolTable &symtab) {
    int index = e.indexOf("[");
    int index2 = e.indexOf("=");
    int index3 = e.indexOf("{");
    QString selectPart = e.mid(index+1, e.size() - index - 2);
    QString inputMap = e.mid(index2+1, index - index2 - 1);
    _inParameters.push_back(Parameter(inputMap, itUNKNOWN, symtab));
    QString outputPart =  index3 == -1 ? e.left(index2) : e.left(index3);
    IlwisTypes valueType =  hasType(_inParameters.back().valuetype(), itCOVERAGE) ? itCOVERAGE : itTABLE;
    _outParameters.push_back(Parameter(outputPart, valueType, symtab));
    int index4=selectPart.indexOf(",");
    if ( index4 == -1) { //either id or number
        bool ok;
        int layer = selectPart.toUInt(&ok);
        if ( ok) {
            _inParameters.push_back(Parameter(QString("\"layer=%1\"").arg(layer),itSTRING,symtab));
        } else {
            _inParameters.push_back(Parameter(QString("\"attribute=%1\"").arg(selectPart), itSTRING, symtab));
        }
    } else {
        QStringList parts = selectPart.split(",");
        if ( parts.size() == 2) {
            _inParameters.push_back(Parameter(QString("\"box=%1\"").arg(selectPart),itSTRING, symtab));
        } else {
           _inParameters.push_back(Parameter(QString("\"polygon=%1\"").arg(selectPart), itSTRING, symtab));
        }
    }
    _name = "selection";

}

void OperationExpression::specialExpressions(const QString &e, const SymbolTable &symtab) {
    //TODO: other cases of special expressions
    _name = "assignment";
    _inParameters.push_back(Parameter(e.mid(e.indexOf("=")+1),itCOVERAGE, symtab));

}

void OperationExpression::parseFunctionExpression(const QString &txt, const SymbolTable &symtab) {
    QString e = txt;
    int index = e.indexOf("(");
    if ( index == -1)
        specialExpressions(txt,symtab);

    QRegExp pattern = QRegExp("[\'\"]");
    int startQuote = e.indexOf(pattern);
    int endQuote = e.indexOf(pattern, startQuote+1 );
    int index2 = e.indexOf("=");
    if ( (index2 > startQuote && index2 < endQuote) || index2 > index)
        index2 = -1;
    if ( index != -1) {
        if ( _name == "") {
            if ( index2 != -1)
                _name = e.mid(index2+1, index - index2 - 1);
            else
                _name = e.left(index);
        }
        _isRemote = _name.indexOf("http://") != -1;
    }

    QString start = e.left(index2);
    int blockCount = 0;
    int quoteCount = 0;
    char quote = '\0';
    int count = 0;
    int cur = 0;
    std::vector<int> outputParams;
    if ( index2 != -1) {
        foreach(const QChar& cu, start) {
            char c = cu.toLatin1();
            if ( c == '{'){
                blockCount++;
            }
            if ( c == '}'){
                blockCount--;
            }
            if ( c == ',' || blockCount == 1)
                outputParams.push_back(count);
            ++count;
        }
        qint32 shift = 0;
        outputParams.push_back(start.size());
        for(int i =0; i < outputParams.size(); ++i) {
            int index3 = outputParams[i];
            QString part = start.mid(cur, index3 - cur) ;
            part = part.trimmed();
            Parameter parm(part,itUNKNOWN, symtab);
            _outParameters.push_back(parm);
            shift = 1;
            cur = index3 + shift;
        }
    }
    std::map<int, int> inputParams;
    int keyword = 0;
    int paramIndex = -1;
    if (index > 0) {
        int len =  e.size() - index - 2;
        QString rest = e.mid(index + 1 , len);
        blockCount = quoteCount = count = 0;
        foreach(const QChar& cu, rest) {
            char c = cu.toLatin1(); // eessions are not internatiolized, so its allowed
            if ( c == '(' && quoteCount == 0)
                blockCount++;
            if ( c == ')' && quoteCount == 0)
                blockCount--;
            if ( (c == '"' || c == '\'') && quoteCount == 0) {
                quoteCount++;
                quote = c;
            }
            else if (  (c == quote) && quoteCount != 0) {
                quoteCount--;
                quote = '\0';
            }

            ++count;
            if ( blockCount == 0 && quoteCount == 0) {
                if (c == ','){
                    if (keyword == 0) {
                        inputParams[++paramIndex] = count;
                    } else if (inputParams.size() == 0){
                        inputParams[keyword] = count;
                    } else {
                        //Probleem
                    }
                } else if ( c == '=' ) {
                    QString value = rest.mid(inputParams[paramIndex], rest.size() - count);
                    // ignore '=' in urls, they are part of the url
                    if ( value.indexOf("://") == -1){
                        keyword = count;
                    }

                }
            }

        }
        cur = 0;
        if ( rest != "") // rest == "" means there are no parameters
            inputParams[keyword == 0 ? ++paramIndex : keyword] = rest.size() + 1;
        int index4 = 0;
        foreach(const auto& input, inputParams) {
            if (keyword > 0) {
                index4 = input.first;
                QString key = rest.mid(cur, index4 - cur - 1);
                key = key.trimmed();
                cur = index4;
                QString value = rest.mid(cur, input.second - cur - 1).trimmed();
                _inParametersMap[key] = Parameter(value, itUNKNOWN, symtab);
            } else {
                QString value = rest.mid(cur, input.second - cur - 1).trimmed();
                _inParameters.insert(input.first, Parameter(value, itUNKNOWN, symtab));
            }
            cur = input.second;
            index4 = 0;
        }
    }
}

Parameter OperationExpression::parm(int index, bool in) const
{
    if (!inputIsKeyword()) {
        const QList<Parameter>& parameters = in ? _inParameters : _outParameters;
        if ( index < parameters.size()) {
                return parameters[index];
        }
    }
    return Parameter();
}

Parameter OperationExpression::parm(const QString searchValue, bool caseInsensitive, bool in) const
{
    if ( !searchValue.isEmpty() ) {
        QString k1 = caseInsensitive ? searchValue.toLower() : searchValue;
        if (inputIsKeyword() && in) {
            if ( caseInsensitive ){
                foreach(const auto& parm, _inParametersMap) {
                    QString k2 = _type == otFunction ? parm.name(): parm.value();
                    k2 = k2.toLower();
                    if ( k1 == k2) {
                        /*if (parm.value() == EXPREMPTYPARAMETER)
                            parm.value("?");*/
                        return parm;
                    }
                }
            } else {
                auto iter = _inParametersMap.find(searchValue);
                if (iter != _inParametersMap.end()) {
                    return (*iter);
                }
            }
        } else {
            const QList<Parameter>& parameters = in ? _inParameters : _outParameters;
            foreach(const Parameter& parm, parameters) {
                QString k2 = _type == otFunction ? parm.name(): parm.value();
                if ( caseInsensitive){
                    k2 = k2.toLower();
                    if ( k1 == k2)
                        return parm;
                } else {
                    if ( k2 == searchValue)
                        return parm;
                }
            }
        }
    }
    return Parameter();
}

QString OperationExpression::name(bool caseInsensitive) const
{
    if ( caseInsensitive)
        return _name.toLower();
    return  _name;
}

bool OperationExpression::matchesParameterCount(const QString& match, bool in) const {
    int count = parameterCount(in);
    if ( match.right(1) == "+") {
        QString n = match.left(match.size() - 1);
        return count >= n.toInt();
    }
    QStringList parts = match.split("|");
    foreach(const QString& part, parts) {
        bool ok;
        int index = part.toInt(&ok);
        if (!ok) {
            return ERROR0("Illegal metdata definition");
        }
        if ( index == count)
            return true;
    }
    return false;


}

int OperationExpression::parameterCount(bool in) const
{
    if (inputIsKeyword() && in) {
        return _inParametersMap.size();
    }
    const QList<Parameter>& parameters = in ? _inParameters : _outParameters;

    return parameters.size();
}

bool OperationExpression::isValid() const
{
    return !_name.isEmpty();
}

bool OperationExpression::isRemote() const
{
    return _isRemote;
}

QUrl Ilwis::OperationExpression::metaUrl(bool simple) const
{
    QString url = _name;
    if ( _name.indexOf("http://") == -1) // names that are already an url are not in the local ilwis://operations,
        url = "ilwis://operations/" + _name;
    if ( !simple) {
        if (inputIsKeyword()){
            for(auto iter = _inParametersMap.begin(); iter != _inParametersMap.end(); iter++) {
                const auto& parm = *iter;
                if (iter == _inParametersMap.begin())
                    url += "?";
                else
                    url += "&";

                url += QString("pin::%1::type=%2").arg(parm.value()).arg(parm.valuetype());
            }
        } else {
            for(int i=0; i < _inParameters.size(); ++i) {
                if ( i == 0)
                    url += "?";
                else
                    url += "&";

                url += QString("pin::%1::type=%2").arg(i).arg(_inParameters[i].valuetype());
            }
        }
        for(int i=0; i < _outParameters.size(); ++i) {
            if ( i == 0)
                url += "?";
            else
                url += "&";

            url += QString("pout::%1::type=%2").arg(i).arg(_outParameters[i].valuetype());
        }
    }
    return QUrl(url);

}

QString OperationExpression::toString(bool rightsideonly) const
{
    QString expression;
    if ( _type == otFunction) {
        if ( rightsideonly == false){
            for(const Parameter& parm : _outParameters) {
                if ( expression != "")
                    expression += ", ";
                if ( expression == "" )
                    expression += "( ";

                expression += parm.value();
            }
            if ( expression != "")
                expression += " ) = ";
        }
        expression += _name;
        expression += "( ";
        int count = 0;
        if (inputIsKeyword()){
            for(auto iter = _inParametersMap.begin(); iter != _inParametersMap.end(); iter++) {
                const Parameter& parm = *iter;
                if ( count++ != 0)
                    expression += ", ";
                expression += parm.value() + "=" + parm.value();
            }
        } else {
            for(const Parameter& parm : _inParameters) {
                if ( count++ != 0)
                    expression += ", ";
                expression += parm.value();
            }
        }
        expression += ")"    ;
    }else{
        for(const Parameter& parm : _inParameters) {
            if ( expression != "")
                expression += " ";
            expression += parm.value();
        }
        return _name + " " + expression;
    }
    //TODO: other cases

    return expression;
}

QString OperationExpression::toPythonExpression() const
{
    QString expr("ilwis.Engine.do(");
    expr += "'"  + name() + "',";
    QStringList parts = parm(0).value().split("=");
    if ( parts.size() == 2){
        QString output = parts[0];
        output.remove(".ilwis");
        int index1 = output.indexOf("{");
        int index2 = output.lastIndexOf("}");
        expr = output + "=" + expr;
        expr.remove(index1, index2 - index1 + 1);

    }
    for(int i=0; i < parameterCount();++i){
        Parameter p = parm(i);
        if ( i > 0)
            expr += ", ";
        if ( p.valuetype() == itSTRING || hasType(p.valuetype(), itILWISOBJECT)){
            expr += "'";
        }
        expr += p.value();

        if ( p.valuetype() == itSTRING || hasType(p.valuetype(), itILWISOBJECT)){
            expr += "'";
        }
    }
    QString wcatalog = context()->workingCatalog()->resource().url().toString();
    expr.remove(wcatalog + "/");
    expr += ")"    ;

    return expr;


}

QString OperationExpression::modifyTableOutputUrl(const QString& output, const QStringList& parms)
{
    QString columnName = output;
    QString firstTable = parms[0];
    if ( firstTable.indexOf("://") != -1){
        int index = firstTable.lastIndexOf("/");
        firstTable = firstTable.mid(index + 1);
        index =  firstTable.indexOf(".");
        if ( index != -1)
            firstTable = firstTable.left(index) ;
    }
    QString internalPath = context()->persistentInternalCatalog().toString();
    QString outpath = internalPath + "/" + output;

    return outpath;

}

QString createOuputName(const Resource& resource, const QString& name) {
    QString path = resource.url(true).toString();
    QFileInfo inf(resource.url(true).toLocalFile());
    bool isf = inf.isFile();
    if (isf) {
        int index = resource.url(true).toString().lastIndexOf("/");
        path = resource.container().toString().mid(0, index);
    }
    path += "/" + name;
    if (path.indexOf(QRegExp("[ ,)(\"\']")) != -1) {
        path = "\"" + path + "\"";
    }
    return path;
}

OperationExpression OperationExpression::createExpression(quint64 operationid, const QString& parameters, bool acceptIncompleteExpressions){
//    if (  parameters == "")
//        return OperationExpression();

    Resource operationresource = mastercatalog()->id2Resource(operationid);
    if ( !operationresource.isValid())
        return OperationExpression();



    QString expression;
    QStringList parms = parameters.split("|");
    bool hasMissingParameters = false;
    std::vector<QString> reserved={"and","or","xor","*","/","mod","not","+","-"};
    QVariant inp =  operationresource["inparameters"];
    int maxinputparameters =inp.isValid() ? inp.toString().split("|").last().toInt() : 0;
    for(int i = 0; i < parms.size(); ++ i){
        if(i < maxinputparameters ){
            if ( expression.size() != 0)
                expression += ",";
            QString parm = parms[i];
            IlwisTypes dataType = operationresource[QString("pin_%1_type").arg(i+1)].toULongLong();
            if ( hasType(dataType, itCOLLECTION)){
                QStringList parts = parm.split("\n");
                QString lst;
                for(QString part : parts){
                    if ( part.trimmed() != ""){
                        if ( lst != "")
                            lst += "|";
                        lst += part;
                    }
                }
                parm = lst;
                parm  = "\"" + parm+ "\"";
            }
            QString p  = QString("pin_%1_needsquotes").arg(i+1);
            bool needsquotes = operationresource.hasProperty(p) ? operationresource[p].toBool() : false;
            if ( !needsquotes && parm.size() > 2 && parm[0] != '\"'){
                if ( parm.indexOf("..") != -1 || parm.indexOf(",") != -1){
                    needsquotes = true;
                }
            }
            auto iter = std::find(reserved.begin(), reserved.end(), parm);
            if ( iter != reserved.end() || needsquotes){
                if ( parm.size() > 1){ // do not quote already quoted strings
                    if ( parm[0] != '\"' )
                        parm  = "\"" + parm+ "\"";
                }

            }
            expression += (parm == "" ?  "?input_" + QString::number(i+1) : parm);
        }

    }

   // if (hasMissingParameters) return OperationExpression();

    QString allOutputsString;

    bool duplicateFileNames = false;

    QStringList parts = operationresource["outparameters"].toString().split("|");
    int maxparms = parts.last().toInt();
    int count = 1;
    QString anonId =  QString::number(Identity::newAnonymousId());
    for(int i=(parms.size() - maxparms); i<parms.size(); ++i){
        QString output = parms[i];
        if ( output == "")
            output =QString("output_%1_%2").arg(operationid).arg(i);


        QString pout = QString("pout_%1_type").arg(count++);

        IlwisTypes outputtype = operationresource[pout].toULongLong();
        if ( output.indexOf("@@") != -1 ){
            QString format;
            QStringList parts = output.split("@@");
            output = parts[0];
            if ( output == ""){
                output = "output_" + anonId + "_" + QString::number(i);
                kernel()->issues()->log(TR("Missing output name; output will be generated with the name:" + output),IssueObject::itWarning);
            }

            //Check if user didnt put the same output name in another output field
            int occurences = 0;
            for(int j=(parms.size() - maxparms); j<parms.size(); ++j){
                QString compareString = parms[j].split("@@")[0];
                if(output == compareString){
                    occurences++;
                }
            }

            //Add the duplicate name to the list of duplicate names
            if(occurences>1){
                duplicateFileNames = true;
                kernel()->issues()->log(TR("Workflow did not execute, multiple occurences of an output name"));
            }
			double resolution = rUNDEF;
			int fnameIndex = parts.size() == 2 ? 1 : 2;
			if (parts.size() == 3) {
				bool ok;
				double v = parts[1].toDouble(&ok);
				if (ok)
					resolution = v;
			}
            QString formatName = parts[fnameIndex];
			if (formatName[0] == "*") // special case with most recently used formats which contain a * before the name
				formatName = formatName.mid(1);

            if ( operationresource.ilwisType() & itWORKFLOW) {
				QDir directory;

				//If not memory
				QString fileName;

				if (formatName == "Temporary") {
					//Get all files in the internal catalog
					QString dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/internalcatalog";
					directory = QDir(dataLocation);
				}
				else {
					//Get all files in the directory
					QString dataLocation = output;
					dataLocation = QUrl(dataLocation).toLocalFile();

					QStringList splitUrl = dataLocation.split("/");

					fileName = splitUrl.last();

					QString query = "name='" + formatName + "'";
					std::multimap<QString, Ilwis::DataFormat>  formats = Ilwis::DataFormat::getSelectedBy(Ilwis::DataFormat::fpNAME, query);
					if (formats.size() == 1) {
						QString connector = (*formats.begin()).second.property(DataFormat::fpCONNECTOR).toString();
						QString code = (*formats.begin()).second.property(DataFormat::fpCODE).toString();

						QVariantList extensions = Ilwis::DataFormat::getFormatProperties(DataFormat::fpEXTENSION, outputtype, connector, code);

						fileName += ".";
						fileName += extensions[0].toString();
					}

					splitUrl.removeLast();

					dataLocation = splitUrl.join("/");

					directory = QDir(dataLocation);
				}

				QStringList existingFileNames = directory.entryList(QStringList() << "*.*", QDir::Files);


                //Check if a file with the same name already exist
                for(int j=0;j<existingFileNames.size();++j){
                    if(formatName == "Temporary"){
                        if(existingFileNames[j] == output) {
                            duplicateFileNames = true;
                            kernel()->issues()->log(TR("Workflow did not execute duplicate name: " + output + ". Please change this name."));
                        }
                    }else{
                        if(existingFileNames[j] == fileName){
                            duplicateFileNames = true;
                            kernel()->issues()->log(TR("Workflow did not execute duplicate name: " + fileName + ". Please change this name."));
                        }
                    }
                }
            }

            if ( hasType(outputtype, itCOLUMN)){
                if ( formatName == "Temporary"){
                    output = modifyTableOutputUrl(output, parms);
                }else
                    output = parms[0] + "[" + output + "]";
            }
            if ( formatName == "Keep original"){
                IIlwisObject obj;
                obj.prepare(parms[0], operationresource["pin_1_type"].toULongLong());
                if ( obj.isValid()){
                    IlwisTypes type = operationresource[pout].toULongLong();
                    QVariantList values = DataFormat::getFormatProperties(DataFormat::fpCODE,type,obj->provider());
                    if ( values.size() != 0){
                        format = "{format(" + obj->provider() + ",\"" + values[0].toString() + "\")";
                    }else{
                        kernel()->issues()->log(QString("No valid conversion found for provider %1 and format %2").arg(obj->provider()).arg(IlwisObject::type2Name(type)));
                        return OperationExpression();
                    }
                }
            }
            //overrule the user if he wants to store things in the internalcatalog, then the format is by defintion stream
            if ( context()->workingCatalog()->resource().url() == INTERNAL_CATALOG_URL)
                formatName == "Temporary";
            if ( formatName != "Temporary"){ // special case
                if ( format == "") {
                    QString query = "name='" + formatName + "' and (readwrite='rc' or readwrite='rcu')";
                    std::multimap<QString, Ilwis::DataFormat>  formats = Ilwis::DataFormat::getSelectedBy(Ilwis::DataFormat::fpNAME, query);
                    if ( formats.size() == 1){
                        format = "{format(" + (*formats.begin()).second.property(DataFormat::fpCONNECTOR).toString() + ",\"" +
                                (*formats.begin()).second.property(DataFormat::fpCODE).toString() + "\")";
                    }
                }
				if (resolution != rUNDEF) {
					format += ";resolution(" + QString::number(resolution) + ")";
				}
				format += "}";
                // if there is no path we extend it with a path unless the output is a new column, output is than the "old" table so no new output object
                if (output.indexOf("://") == -1) {
                    output = createOuputName(context()->workingCatalog()->resource(), output);
                    output += format;
                   // output = context()->workingCatalog()->resource().url().toString() + "/" + output + format;
                }
                else
                    output = output + format;
            }else{
                if ( hasType(outputtype,itRASTER)){
                    format = "{format(stream,\"rastercoverage\")";
                }else if (hasType(outputtype, itFEATURE)){
                    format = "{format(stream,\"featurecoverage\")";
                }else if (hasType(outputtype, itTABLE | itCOLUMN)){
                    format = "{format(stream,\"table\")";
                }else if (hasType(outputtype, itCATALOG)){
                    format = "{format(stream,\"catalog\")";
                }else if (hasType(outputtype, itDOMAIN)){
                    format = "{format(stream,\"domain\")";
                }else if (hasType(outputtype, itCOORDSYSTEM)){
                    format = "{format(stream,\"coordinatesystem\")";
                }else if (hasType(outputtype, itGEOREF)){
                    format = "{format(stream,\"georeference\")";
                }
                if ( formatName == "Temporary"){
                    if ( output.indexOf(".ilwis")== -1)
                        output += ".ilwis";
                }
				if (resolution != rUNDEF) {
					format += ";resolution(" + QString::number(resolution) + ")";
				}
				format += "}";
                output = output + format;
            }
        }

        if(!allOutputsString.isEmpty()){
            allOutputsString.append(",");
        }
        allOutputsString += output;
    }

    if(!duplicateFileNames){
        QString opname = operationresource.name();
        opname.remove(".ilwis");
        if ( allOutputsString == "")
            expression = QString("script %1(%2)").arg(opname).arg(expression);
        else
            expression = QString("script %1=%2(%3)").arg(allOutputsString).arg(opname).arg(expression);

        OperationExpression opExpr(expression);

        return opExpr;
    }
    return OperationExpression();
}







