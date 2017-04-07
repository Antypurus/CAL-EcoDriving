
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
	GraphViewer *gv = new GraphViewer(1280, 720, true);
	std::unordered_map<size_t, int> referenceTable;

	gv->setBackground("background.jpg");

	gv->createWindow(1280, 720);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	Linker a;
	std::cout << "Nodes:" << a.nodes.size() << std::endl;
	std::cout << "Connections:" << a.conections.size() << std::endl;
	std::cout << "Ways:" << a.ways.size() << std::endl;
	std::cout << "Node Locations:" << a.locationNodes.size() << std::endl;

	EcoDriving::EcoVehicle::ElectricVehicle car(0,0,0,100,1000);

	int d = 0;
	Graph<EcoDriving::Location::Location> locationGraph;
	for (auto it = a.locationNodes.begin(); it != a.locationNodes.end(); ++it) {
		locationGraph.addVertex(it->second);
		referenceTable.insert(std::make_pair(it->first, d));
		gv->addNode(d, it->second.getCoordinates().x, it->second.getCoordinates().y);
		//cout << "X:" << it->second.getCoordinates().x << std::endl;
		//cout << "Y:" << it->second.getCoordinates().y << std::endl;
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
			//cout << "Weight:" << weight << endl;
			gv->addEdge(c, referenceTable[src.getNodeID()], referenceTable[dst.getNodeID()], EdgeType::DIRECTED);

			//cout << "Link:" << src.getNodeID() << "," << dst.getNodeID() << endl;

			locationGraph.addEdge(src, dst, weight);
		}
	}
	cout << "Number of Links:" << c << endl;

	locationGraph.dijkstraShortestPath(a.locationNodes[2273202419]);
	EcoDriving::Location::Location str = a.locationNodes[2273202419];
	EcoDriving::Location::Location end = a.locationNodes[2273202427];
	vector<EcoDriving::Location::Location> res = locationGraph.getPathToOrigin(str, end);
	Vertex<EcoDriving::Location::Location> check = *(locationGraph.getVertex(str));
	std::vector<EcoDriving::Location::Location> conecCount = locationGraph.bfs(&check);

	std::cout << "Size:" << conecCount.size() << std::endl;

	if (conecCount.size() == a.locationNodes.size()) {
		std::cout << "This Graph Is Connected" << std::endl;
	}
	else {
		std::cout << "This Graph Is Not Connected" << std::endl;
	}

	for (int i = 0; i < res.size(); i++) {
		cout << "ID:" << res[i].getNodeID() << endl;
	}

	std::cout << "Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;
	gv->rearrange();
	getchar();
	return;
}