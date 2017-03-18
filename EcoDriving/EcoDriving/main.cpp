
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>

void main(void) {
	
	std::unordered_map<size_t, EcoDriving::Parsers::Node>nodes;

	EcoDriving::Linker::NodeParser(nodes, "map.txt");

	EcoDriving::Parsers::Node a = nodes[0];

	std::cout << a.getNodeID();
	
	system("pause");

	return;
}