
#include "OSMParser.h"
#include <unordered_map>
#include "Graph.h"
#include "Location.h"
#include "ElectricVehicle.h"
#include "PROJECT_SETTINGS_MACROS.h"
#include "CoordinateSystem.h"
#include "MATH_CONSTANTS_MACROS.h"
#include <unordered_map>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace EcoDriving::Linker;

void main(void) {
	GraphViewer *gv = new GraphViewer(1280, 720, false);
	std::unordered_map<size_t, int> referenceTable;
	std::unordered_map<int, size_t> referenceTable2;

	gv->setBackground("background.jpg");

	gv->createWindow(1280, 720);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	Linker a;

#if DISPLAY_METRICS
	std::cout << "@Metrics:: Nodes:" << a.nodes.size() << std::endl;
	std::cout << "@Metrics:: Connections:" << a.conections.size() << std::endl;
	std::cout << "@Metrics:: Ways:" << a.ways.size() << std::endl;
	std::cout << "@Metrics:: Node Locations:" << a.locationNodes.size() << std::endl;
#endif

	double minX = a.locationNodes.begin()->second.getCoordinates().x;
	double minY = a.locationNodes.begin()->second.getCoordinates().y;

	for (auto it = a.locationNodes.begin(); it != a.locationNodes.end(); ++it) {
		double keepX = it->second.getCoordinates().x;
		double keepY = it->second.getCoordinates().y;
		if (keepX < minX) {
			minX = keepX;
		}
		if (keepY < minY) {
			minY = keepY;
		}
	}

	EcoDriving::EcoVehicle::ElectricVehicle car(0,0,0,100,1000);

	int d = 0;
	Graph<EcoDriving::Location::Location> locationGraph;
	Graph<EcoDriving::Location::Location> reverseGraph;
	for (auto it = a.locationNodes.begin(); it != a.locationNodes.end(); ++it) {
		locationGraph.addVertex(it->second);
		reverseGraph.addVertex(it->second);
		referenceTable.insert(std::make_pair(it->first, d));
		referenceTable2.insert(std::make_pair(d, it->first));
		gv->addNode(d, (it->second.getCoordinates().x - minX) * 2, (it->second.getCoordinates().y - minY));
		if (it->second.getRecharge()) {
			gv->setVertexColor(d, "pink");
			gv->setVertexLabel(d, "Recharge Station | ID:"+to_string(d));
		}

#if DISPLAY_METRICS
		cout << "@Metrics:: X:" << it->second.getCoordinates().x << std::endl;
		cout << "@Metrics:: Y:" << it->second.getCoordinates().y << std::endl;
#endif

		d++;
	}
	int c = 0;
	for (auto it = a.conections.begin(); it != a.conections.end(); ++it) {
		std::vector<std::pair<size_t, size_t>> edges = it->second.getEdges();
		for (int i = 0; i < edges.size(); i++) {
			c++;
			EcoDriving::Location::Location src = a.locationNodes[edges[i].first];
			EcoDriving::Location::Location dst = a.locationNodes[edges[i].second];

			double distance = src.getCoordinates().distanceCalculation(dst.getCoordinates());
			double timeToArrival = distance * car.getVelocity();
			double heightDiff = dst.getCoordinates().altitude - src.getCoordinates().altitude;

			double usedBattery = 0;
			if (heightDiff == 0) {
				usedBattery = distance*FLAT_ENERGY_COST;
			}
			else if (heightDiff < 0) {
				usedBattery = -distance*DOWN_HILL_REFENERATION;
			}
			else if (heightDiff > 0) {
				usedBattery = distance*UP_HILL_ENERGY_COST;
			}

			double weight = usedBattery;

#if DISPLAY_METRICS
			cout << "@Metrics:: Weight:" << weight << endl
#endif

			gv->addEdge(c, referenceTable[src.getNodeID()], referenceTable[dst.getNodeID()], EdgeType::DIRECTED);

#if DISPLAY_METRICS
			cout << "@Metrics:: Link:" << src.getNodeID() << "," << dst.getNodeID() << endl;
#endif

			locationGraph.addEdge(src, dst, weight);
			reverseGraph.addEdge(dst, src, weight);
		}
	}

#if DISPLAY_METRICS
	cout << "@Metrics:: Number of Links:" << c << endl;
#endif

	gv->rearrange();

	size_t srcID = 2273202419;
	size_t dstID = 2273202427;

	cout << "Source ID:";
	cin >> srcID;
	cout << "Destination ID:";
	cin >> dstID;

	locationGraph.dijkstraShortestPath(a.locationNodes[referenceTable2[srcID]]);
	EcoDriving::Location::Location str = a.locationNodes[referenceTable2[srcID]];
	EcoDriving::Location::Location end = a.locationNodes[referenceTable2[dstID]];
	vector<EcoDriving::Location::Location> res = locationGraph.getPathToOrigin(str, end);
	Vertex<EcoDriving::Location::Location> check = *(locationGraph.getVertex(str));
	std::vector<EcoDriving::Location::Location> conecCount = locationGraph.bfs(&check);//normal graph list of nodes able to reach
	Vertex<EcoDriving::Location::Location> check2 = *(locationGraph.getVertex(str));
	std::vector<EcoDriving::Location::Location> conecCount2 = reverseGraph.bfs(&check2);//reverse graph list of node able to reach

#if DISPLAY_METRICS
	std::cout << "@Metrics:: Connected Vertexes From Reference Point:" << conecCount.size() << std::endl;
#endif

	if (conecCount.size() == a.locationNodes.size()&& conecCount2.size() == a.locationNodes.size()) {
		std::cout << "@GraphInfo:: Conectivity:: This Graph Is Strongly Connected" << std::endl;
	}
	else {
		std::cout << "@GraphInfo:: Conectivity:: This Graph Is Not Connected" << std::endl;
	}

	std::cout << "@GraphInfo:: Path From " << referenceTable2[srcID] << " To " << referenceTable2[dstID] << std::endl;

	for (int i = 0; i < res.size(); i++) {
		cout << "@GraphInfo:: ID:" << res[i].getNodeID() << endl;
		gv->setVertexColor(referenceTable[res[i].getNodeID()], "yellow");
		if (i != res.size()-1) {
			gv->setVertexLabel(referenceTable[res[i].getNodeID()], "GO HERE");
		}
		else {
			gv->setVertexLabel(referenceTable[res[i].getNodeID()], "START HERE");
		}
	}

	std::cout << "@GraphInfo:: Path Finished" << std::endl;

#if DISPLAY_METRICS
	std::cout << "@Metrics:: Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;
#endif

	gv->rearrange();
	system("pause");
	return;
}