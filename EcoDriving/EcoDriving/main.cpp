
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>

using namespace EcoDriving::Linker;

void main(void) {

	Linker a;

	std::cout << "Nodes:" << a.nodes.size() << std::endl;
	std::cout << "Conections:" << a.conections.size() << std::endl;
	std::cout << "Ways:" << a.ways.size() << std::endl;
	std::cout << "Node Locations:" << a.locationNodes.size() << std::endl;

	system("pause");
	return;
}