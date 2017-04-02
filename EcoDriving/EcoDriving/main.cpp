
#include "OSMParser.h"
#include <iostream>
#include <unordered_map>
#include "Graph.h"
#include "Location.h"
#include "ElectricVehicle.h"
#include "PROJECT_SETTINGS_MACROS.h"
#include "CoordinateSystem.h"
#include "MATH_CONSTANTS_MACROS.h"

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
		std::vector<std::pair<size_t, size_t>> edges = it->second.getEdges();
		for (int i = 0; i < edges.size(); i++) {
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

			double weight = usedBattery + distance + timeToArrival;
			//cout << "Weight:" << weight << endl;

			locationGraph.addEdge(src, dst, weight);
		}
	}

	std::cout << "Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;

	system("pause");
	return;
}