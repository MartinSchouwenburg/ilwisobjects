/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2010 Sandro Santilli <strk@keybit.net>
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: operation/polygonize/Polygonizer.java rev. 1.6 (JTS-1.10)
 *
 **********************************************************************/

#include <geos/operation/polygonize/Polygonizer.h>
#include <geos/operation/polygonize/PolygonizeGraph.h>
#include <geos/operation/polygonize/EdgeRing.h>
#include <geos/geom/LineString.h>
#include <geos/geom/Geometry.h>
#include <geos/geom/Polygon.h>
#include <geos/util/Interrupt.h>
// std
#include <vector>

#ifdef _MSC_VER
#pragma warning(disable:4355)
#endif

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

using namespace std;
using namespace geos::geom;

namespace geos {
namespace operation { // geos.operation
namespace polygonize { // geos.operation.polygonize

Polygonizer::LineStringAdder::LineStringAdder(Polygonizer *p):
	pol(p)
{
}

void
Polygonizer::LineStringAdder::filter_ro(const Geometry *g)
{
	const LineString *ls = dynamic_cast<const LineString *>(g);
	if ( ls ) pol->add(ls);
}


/*
 * Create a polygonizer with the same GeometryFactory
 * as the input Geometry
 */
Polygonizer::Polygonizer():
	lineStringAdder(this), 
	graph(NULL),
	dangles(),
	cutEdges(),
	invalidRingLines(),
	holeList(),
	shellList(),
	polyList(NULL)
{
}

Polygonizer::~Polygonizer()
{
	delete graph;

	for (unsigned int i=0, n=invalidRingLines.size(); i<n; ++i)
		delete invalidRingLines[i];

	if ( polyList )
	{
		for (unsigned int i=0, n=polyList->size(); i<n; ++i)
			delete (*polyList)[i];
		delete polyList;
	}
}

/*
 * Add a collection of geometries to be polygonized.
 * May be called multiple times.
 * Any dimension of Geometry may be added;
 * the constituent linework will be extracted and used
 *
 * @param geomList a list of {@link Geometry}s with linework to be polygonized
 */
void
Polygonizer::add(vector<Geometry*> *geomList)
{
	for(unsigned int i=0, n=geomList->size(); i<n; ++i)
	{
		const Geometry *geometry=(*geomList)[i];
		add(geometry);
	}
}

/*
 * Add a collection of geometries to be polygonized.
 * May be called multiple times.
 * Any dimension of Geometry may be added;
 * the constituent linework will be extracted and used
 *
 * @param geomList a list of {@link Geometry}s with linework to be polygonized
 */
void
Polygonizer::add(vector<const Geometry*> *geomList)
{
	for(unsigned int i=0, n=geomList->size(); i<n; ++i)
	{
		const Geometry *geometry=(*geomList)[i];
		add(geometry);
	}
}

/*
 * Add a geometry to the linework to be polygonized.
 * May be called multiple times.
 * Any dimension of Geometry may be added;
 * the constituent linework will be extracted and used
 *
 * @param g a Geometry with linework to be polygonized
 */
void
Polygonizer::add(Geometry *g)
{
	g->apply_ro(&lineStringAdder);
}

/*
 * Add a geometry to the linework to be polygonized.
 * May be called multiple times.
 * Any dimension of Geometry may be added;
 * the constituent linework will be extracted and used
 *
 * @param g a Geometry with linework to be polygonized
 */
void
Polygonizer::add(const Geometry *g)
{
	g->apply_ro(&lineStringAdder);
}

/*
 * Add a linestring to the graph of polygon edges.
 *
 * @param line the LineString to add
 */
void
Polygonizer::add(const LineString *line)
{
	// create a new graph using the factory from the input Geometry
	if (graph==NULL)
		graph=new PolygonizeGraph(line->getFactory());
	graph->addEdge(line);
}

/*
 * Gets the list of polygons formed by the polygonization.
 * @return a collection of Polygons
 */
vector<Polygon*>*
Polygonizer::getPolygons()
{
	polygonize();
	vector<Polygon *> *ret = polyList;
	polyList = NULL;
	return ret;
}

/* public */
const vector<const LineString*>&
Polygonizer::getDangles()
{
	polygonize();
	return dangles;
}

/* public */
const vector<const LineString*>&
Polygonizer::getCutEdges()
{
	polygonize();
	return cutEdges;
}

/* public */
const vector<LineString*>&
Polygonizer::getInvalidRingLines()
{
	polygonize();
	return invalidRingLines;
}

/* public */
void
Polygonizer::polygonize()
{
	// check if already computed
	if (polyList!=NULL) return;

	polyList=new vector<Polygon*>();

	// if no geometries were supplied it's possible graph could be null
	if (graph==NULL) return; 

	graph->deleteDangles(dangles);

	graph->deleteCutEdges(cutEdges);

	vector<EdgeRing*> edgeRingList;
	graph->getEdgeRings(edgeRingList);
#if GEOS_DEBUG
	cerr<<"Polygonizer::polygonize(): "<<edgeRingList.size()<<" edgeRings in graph"<<endl;
#endif
	vector<EdgeRing*> validEdgeRingList;
	invalidRingLines.clear(); /* what if it was populated already ? we should clean ! */
	findValidRings(edgeRingList, validEdgeRingList, invalidRingLines);
#if GEOS_DEBUG
	cerr<<"                           "<<validEdgeRingList.size()<<" valid"<<endl;
	cerr<<"                           "<<invalidRingLines.size()<<" invalid"<<endl;
#endif

	findShellsAndHoles(validEdgeRingList);
#if GEOS_DEBUG
	cerr<<"                           "<<holeList.size()<<" holes"<<endl;
	cerr<<"                           "<<shellList.size()<<" shells"<<endl;
#endif

	assignHolesToShells(holeList, shellList);

	for (unsigned int i=0, n=shellList.size(); i<n; ++i)
	{
		EdgeRing *er=shellList[i];
		polyList->push_back(er->getPolygon());
	}
}

/* private */
void
Polygonizer::findValidRings(const vector<EdgeRing*>& edgeRingList,
	vector<EdgeRing*>& validEdgeRingList,
	vector<LineString*>& invalidRingList)
{
	typedef vector<EdgeRing*> EdgeRingList;
	
	for (EdgeRingList::size_type i=0, n=edgeRingList.size(); i<n; ++i)
	{
		EdgeRing *er = edgeRingList[i];
		if (er->isValid())
		{
			validEdgeRingList.push_back(er);
		}
		else
		{
			// NOTE: polygonize::EdgeRing::getLineString
			// returned LineString ownership is transferred.
			invalidRingList.push_back(er->getLineString());
		}
		GEOS_CHECK_FOR_INTERRUPTS();
	}
}

/* private */
void
Polygonizer::findShellsAndHoles(const vector<EdgeRing*>& edgeRingList)
{
	holeList.clear(); 
	shellList.clear();
	for (unsigned int i=0, n=edgeRingList.size(); i<n; ++i)
	{
		EdgeRing *er=edgeRingList[i];
		if (er->isHole())
			holeList.push_back(er);
		else
			shellList.push_back(er);
		GEOS_CHECK_FOR_INTERRUPTS();
	}
}

/* private */
void
Polygonizer::assignHolesToShells(const vector<EdgeRing*>& holeList, vector<EdgeRing*>& shellList)
{
	for (unsigned int i=0, n=holeList.size(); i<n; ++i)
	{
		EdgeRing *holeER=holeList[i];
		assignHoleToShell(holeER, shellList);
		GEOS_CHECK_FOR_INTERRUPTS();
	}
}

/* private */
void
Polygonizer::assignHoleToShell(EdgeRing *holeER,
		vector<EdgeRing*>& shellList)
{
	EdgeRing *shell = EdgeRing::findEdgeRingContaining(holeER, &shellList);

	if (shell!=NULL)
		shell->addHole(holeER->getRingOwnership());
}


} // namespace geos.operation.polygonize
} // namespace geos.operation
} // namespace geos

