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
#include "version.h"
#include "connectorinterface.h"
#include "abstractfactory.h"
#include "ilwisobjectfactory.h"
#include "connectorfactory.h"
#include "catalogconnectorfactory.h"
#include "mastercatalog.h"
#include "ilwisobjectconnector.h"
#include "catalogexplorer.h"
#include "catalogconnector.h"
#include "streamobjectfactory.h"
#include "streamconnector.h"
#include "connectorinterface.h"
#include "ilwiscontext.h"
#include "streammodule.h"
#include "versioneddatastreamfactory.h"
#include "versionedserializer.h"
#include "coordinatesystemserializerv1.h"
#include "domainserializerv1.h"
#include "coverageserializerv1.h"
#include "featureserializerv1.h"
#include "tableserializerv1.h"
#include "projectionserializerv1.h"
#include "ellipsoidserializerv1.h"
#include "georefserializerv1.h"
#include "rasterserializerv1.h"
#include "catalogserializerv1.h"
#include "operationmetadataserializerv1.h"
#include "workflowserializerv1.h"
#include "scriptserializerv1.h"
#include "modelserializerv1.h"
#include "combinationmatrixserializerv1.h"
#include "representationserializer.h"
#include "dataformat.h"

using namespace Ilwis;
using namespace Stream;

StreamModule::StreamModule(QObject *parent) : Module(parent, "StreamModule", "iv40","1.0")
{

}

StreamModule::~StreamModule()
{

}

QString StreamModule::getInterfaceVersion() const
{
      return "iv40";
}

QString StreamModule::getName() const
{
    return "stream plugin";
}

QString StreamModule::getVersion() const
{
    return "1.0";
}

void StreamModule::prepare()
{

    StreamObjectFactory *factory = new StreamObjectFactory();
    factory->prepare();
    kernel()->addFactory(factory );


    VersionedDataStreamFactory *versionFactory = new VersionedDataStreamFactory();
    kernel()->addFactory(versionFactory);

	QString supportedVersions = Version::interfaceVersion40 + '|' + Version::interfaceVersion41 + '|' + Version::interfaceVersion42;
    versionFactory->addCreator(supportedVersions,itFEATURE,FeatureSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itDOMAIN,DomainSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itTABLE,TableSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itCOORDSYSTEM,CoordinateSystemSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itELLIPSOID,EllipsoidSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itPROJECTION,ProjectionSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itGEOREF,GeorefSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itRASTER,RasterSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itCATALOG,CatalogserializerV1::create);
    versionFactory->addCreator(supportedVersions,itSINGLEOPERATION,OperationMetadataSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itWORKFLOW,WorkflowSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itSCRIPT,ScriptSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itMODEL,ModelSerializerV1::create);
    versionFactory->addCreator(supportedVersions,itCOMBINATIONMATRIX,CombinationMatrixSerializerv1::create);
	versionFactory->addCreator(supportedVersions, itREPRESENTATION, RepresentationSerializerV1::create);


    ConnectorFactory *cfactory = kernel()->factory<ConnectorFactory>("ilwis::ConnectorFactory");
    if (!cfactory)
        return ;

  //inputconnectors
    cfactory->addCreator(itCOVERAGE|itDOMAIN|itGEOREF|itCOORDSYSTEM|itREPRESENTATION|itELLIPSOID|itPROJECTION|itTABLE|
                         itOPERATIONMETADATA|itMODEL|itSCRIPT|itCOMBINATIONMATRIX  ,"stream", StreamConnector::create);
    cfactory->addCreator(itCATALOG,"stream", CatalogConnector::create);

    //outputconnectors
    cfactory->addCreator("featurecoverage","stream",StreamConnector::create);
    cfactory->addCreator("rastercoverage","stream",StreamConnector::create);
    cfactory->addCreator("table","stream",StreamConnector::create);
    cfactory->addCreator("catalog","stream",StreamConnector::create);
    cfactory->addCreator("domain","stream",StreamConnector::create);
    cfactory->addCreator("itemdomain","stream",StreamConnector::create);
    cfactory->addCreator("textdomain","stream",StreamConnector::create);
    cfactory->addCreator("colordomain","stream",StreamConnector::create);
    cfactory->addCreator("georeference","stream",StreamConnector::create);
    cfactory->addCreator("coordinatesystem","stream",StreamConnector::create);
  cfactory->addCreator("conventionalcoordinatesystem","stream",StreamConnector::create);
    cfactory->addCreator("boundsonlycoordinatesystem","stream",StreamConnector::create);
    cfactory->addCreator("operationmetadata","stream",StreamConnector::create);
    cfactory->addCreator("workflow","stream",StreamConnector::create);
    cfactory->addCreator("script","stream",StreamConnector::create);
    cfactory->addCreator("model","stream",StreamConnector::create);
    cfactory->addCreator("combinationmatrix","stream",StreamConnector::create);
	cfactory->addCreator("representation", "stream", StreamConnector::create);

    QFileInfo ilw = context()->ilwisFolder();
    QString path = ilw.canonicalFilePath() + "/extensions/streamconnector/resources";
    DataFormat::setFormatInfo(path + "/streamformats.config","stream");

    IlwisObject::addTypeFunction(StreamModule::ilwisType);

    kernel()->issues()->log("Loaded streaming module",IssueObject::itMessage);
}

IlwisTypes StreamModule::ilwisType(const QString &name) {
    if ( name.indexOf(".ilwis") > 0){
        Resource res = mastercatalog()->name2Resource(name);
        return res.ilwisType();
    }
    return itUNKNOWN;
}
