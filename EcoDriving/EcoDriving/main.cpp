
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>
#include"Graph.h"
#include"Location.h"
#include "ElectricVehicle.h"
#include "PROJECT_SETTINGS_MACROS.h"

using namespace EcoDriving::Linker;

void main(void) {

	Linker a;
	int c = 0;
	std::cout << "Nodes:" << a.nodes.size() << std::endl;
	std::cout << "Connections:" << a.conections.size() << std::endl;
	std::cout << "Ways:" << a.ways.size() << std::endl;
	std::cout << "Node Locations:" << a.locationNodes.size() << std::endl;

	EcoDriving::EcoVehicle::ElectricVehicle car(0,0,0,100,1000);

	Graph<EcoDriving::Location::Location> locationGraph;
	for (auto it = a.nodes.begin(); it != a.nodes.end(); ++it) {
		locationGraph.addVertex(it->second);
	}
	for (auto it = a.conections.begin(); it != a.conections.end(); ++it) {
		size_t srcID, dstID,wayID;
		wayID = it->first;
		srcID = it->second.getSrcID();
		dstID = it->second.getDstID();
		for (unsigned int i = 0; i < it->second.getEdges().size(); i++) {
			c++;
			typename std::pair<size_t, size_t> edgePair = it->second.getEdges()[i];
			EcoDriving::Location::Location src = a.locationNodes[edgePair.first];
			EcoDriving::Location::Location dst = a.locationNodes[edgePair.second];
			locationGraph.addEdge(src, dst, 0);

#if DISPLAY_METRICS
			cout << "Added Edge Number:" << c << endl;
#endif

		}
	}

	std::cout << "Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;

	system("pause");
	return;
}