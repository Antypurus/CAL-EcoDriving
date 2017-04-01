
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>
#include"Graph.h"
#include"Location.h"

using namespace EcoDriving::Linker;

void main(void) {

	Linker a;

	std::cout << "Nodes:" << a.nodes.size() << std::endl;
	std::cout << "Conections:" << a.conections.size() << std::endl;
	std::cout << "Ways:" << a.ways.size() << std::endl;
	std::cout << "Node Locations:" << a.locationNodes.size() << std::endl;

	Graph<EcoDriving::Location::Location> locationGraph;
	for (auto it = a.nodes.begin(); it != a.nodes.end(); ++it) {
		locationGraph.addVertex(it->second);
	}
	for (auto it = a.conections.begin(); it != a.conections.end(); ++it) {
		size_t srcID, dstID,wayID;
		wayID = it->first;
		srcID = it->second.getSrcID();
		dstID = it->second.getDstID();
		EcoDriving::Location::Location src = a.locationNodes[srcID];
		EcoDriving::Location::Location dst = a.locationNodes[dstID];
		locationGraph.addEdge(src, dst, 0);
	}

	std::cout << "Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;

	system("pause");
	return;
}