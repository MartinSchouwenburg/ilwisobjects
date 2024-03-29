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
#include "version.h"
#include "connectorinterface.h"
#include "versionedserializer.h"
#include "factory.h"
#include "abstractfactory.h"
#include "domain.h"
#include "datadefinition.h"
#include "versioneddatastreamfactory.h"
#include "ilwisobjectconnector.h"
#include "representation.h"
#include "streamconnector.h"
#include "operationhelper.h"

using namespace Ilwis;
using namespace Stream;

VersionedSerializer::VersionedSerializer(QDataStream& stream, const QString &version) : _stream(stream), _version(version)
{
}

VersionedSerializer::~VersionedSerializer()
{

}

bool VersionedSerializer::loadItems(std::vector<Resource> &){
    QString var;
    _stream >> var;
    _stream >> var;
    _stream >> var;
    bool readonly;
    _stream >> readonly;
    double time;
    _stream >> time;
    _stream >> time;

    return true;
}

bool VersionedSerializer::dataIsLoaded() const
{
    return _dataLoaded;
}

bool VersionedSerializer::loadMetaData(IlwisObject *obj, const IOOptions &)
{
    if ( obj->isReadOnly())
        return false;
    bool skip =  obj->resource().isValid();
    skip = skip && hasType(obj->ilwisType(), itCATALOG | itCOVERAGE);
    // we are not going to replace info in the resource if not needed.
    // reason is that this can be a container object (e.g multiband raster) and we are reading here the container
    // and not the actual object embedded in the container
 IlwisTypes tp;
    _stream >> tp;
    if (!skip && obj->extendedType() == itUNKNOWN)
        obj->extendedType(tp);
    QString var,code;
    _stream >> var;
    _stream >> code;
    if (!skip)
        obj->code(code);
    if (!skip ){
        if ( var.indexOf("|")!= -1){
            QStringList parts = var.split("|");
            obj->name(parts[0]);
            obj->resourceRef().addProperty("longname",parts[1]);

        } else
            obj->name(var);
    }

    _stream >> var;
    if (!skip)
        obj->setDescription(var);
    bool readonly;
    _stream >> readonly;
    if (!skip)
        obj->readOnly(readonly);


    double time;
    _stream >> time;
    if (!skip)
        obj->modifiedTime(time);
    _stream >> time;
    if (!skip)
        obj->createTime(time);

	if (_version != Version::interfaceVersion40) {
		quint32 nrMetaItem;
		_stream >> nrMetaItem;
		for (int i = 0; i < nrMetaItem; ++i) {
			QString tag, value;
			_stream >> tag;
			_stream >> value;
			obj->resourceRef().addMetaTag(tag, value);
		}
	}

    return true;

}

bool VersionedSerializer::store(IlwisObject *obj, const IOOptions &options)
{
    double mtime = (double)obj->modifiedTime();
    double ctime = (double)obj->createTime();
    Resource res = obj->resource(IlwisObject::cmINPUT);
    QString nm =  res.hasProperty("longname") ? obj->name() + "|" + res["longname"].toString() : obj->name();
	if (options.find("storename") != options.end())
		nm = options.value("storename").toString();
    _stream <<  obj->ilwisType() << _version << obj->extendedType() << nm << obj->code() << obj->description() << obj->isReadOnly()  << mtime << ctime;
	auto metadata = res.metadata();
	quint32 sz = metadata.size();
	_stream << sz;
	for (auto item : metadata) {
		_stream << item.first;
		_stream << item.second;
	}

	return true;
}

void VersionedSerializer::connector(StreamConnector *streamconnector)
{
    _streamconnector = streamconnector;
}


bool VersionedSerializer::storeDataDefintion(const DataDefinition &def, QDataStream &stream, const IOOptions &options) const
{
    VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
    if (!factory)
        return false;
    std::unique_ptr<DataInterface> domainStreamer(factory->create(Version::interfaceVersion42, itDOMAIN,_stream));
    if ( !domainStreamer)
        return false;
    _stream << def.domain()->valueType();
    storeSystemPath(def.domain()->resource());
    domainStreamer->store(def.domain().ptr(), options);
    if ( !def.range().isNull()) // no range for textdomains
        def.range()->store(_stream);

	std::unique_ptr<DataInterface> rprStreamer(factory->create(Version::interfaceVersion42, itREPRESENTATION, _stream));
	if (!rprStreamer)
		return false;

	storeSystemPath(def.representation()->resource());
	rprStreamer->store(def.representation().ptr(), options);
    return true;
}

bool VersionedSerializer::loadDataDefinition(DataDefinition &def, QDataStream &stream,const IOOptions &options)
{
    VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
    if (!factory)
        return false;
    IlwisTypes valueType, type;
    QString version, url;
    _stream >> valueType;
    _stream >> url;
    _stream >> type;
    _stream >> version;
    std::unique_ptr<DataInterface> domainStreamer(factory->create(version, itDOMAIN,_stream));
    if ( !domainStreamer)
        return false;

    IDomain systemDomain = makeSystemObject<IDomain>(url);
    IDomain dom(type | valueType);
    Range *range = 0;
    domainStreamer->loadMetaData(dom.ptr(), options);
    if ( type != itTEXTDOMAIN){
        range = Range::create(dom->valueType());
        if (!range)
            return false;
        range->load(_stream);
    }
    def = DataDefinition(systemDomain.isValid() ? systemDomain : dom,range);

	if (_version != "iv40" && _version != "iv41") {
		_stream >> url;
		_stream >> type;
		_stream >> version;
		std::unique_ptr<DataInterface> rprStreamer(factory->create(version, itREPRESENTATION, _stream));
		if (!rprStreamer)
			return false;

		IRepresentation systemRpr = makeSystemObject<IRepresentation>(url);
		IRepresentation rpr(type);
		rprStreamer->loadMetaData(rpr.ptr(), options);
		def.representation(systemRpr.isValid() ? systemRpr: rpr);
	}

    return true;
}

void VersionedSerializer::storeSystemPath(const Resource &resource) const
{
    QString path = resource.url().toString();
    if ( path.indexOf("ilwis://system") == 0)
        _stream << resource.url().toString(); // this string is (potentially) only usefull if it is a system object.
    else
        _stream << QString(sUNDEF);
}

bool VersionedSerializer::store(const QString& v, IlwisTypes valueType,const IOOptions &options){

    if ( hasType(valueType, itILWISOBJECT)){
        bool storeall = options.contains("storeall") ? options["storall"].toBool() : false;
        _stream << storeall;
        if ( storeall){
            VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
            std::unique_ptr<DataInterface>  streamer(factory->create(Version::interfaceVersion41, valueType,_stream));
            if ( !streamer)
                return false;
            IIlwisObject obj;
            obj.prepare(v, valueType);
            if ( obj.isValid())
                return streamer->store( obj.ptr(), options);
            return true;
        }
        _stream << v;
    }else {
        _stream << v;
    }
    return true;
}

bool VersionedSerializer::loadMetaData(const Ilwis::IOOptions &options, IlwisTypes tp, QString &v)
{
    if ( hasType(tp, itILWISOBJECT)){
        bool storeall;
        _stream >> storeall;
        if ( storeall){
            VersionedDataStreamFactory *factory = kernel()->factory<VersionedDataStreamFactory>("ilwis::VersionedDataStreamFactory");
            std::unique_ptr<DataInterface>  streamer(factory->create(Version::interfaceVersion41, tp,_stream));
            if ( !streamer)
                return false;
            IIlwisObject obj ;// TODO : this wwont work :)
            return streamer->loadMetaData( obj.ptr(), options);
        }else {
            _stream >> v;
            return true;
        }
    }else {
        _stream >> v;
    }
    return true;
}

IOOptions VersionedSerializer::addParent(IlwisObject *obj, const IOOptions& oldOptions) {
	
	if (!oldOptions.contains("parentid")) {
		IOOptions newOptions = oldOptions;
		newOptions.addOption("parentid", obj->id());
		return newOptions;
	}
	return oldOptions;
}


