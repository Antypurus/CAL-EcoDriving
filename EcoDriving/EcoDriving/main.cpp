
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>

void main(void) {
	
	std::unordered_map<size_t, EcoDriving::Parsers::Node>nodes;

	EcoDriving::Linker::NodeParser(nodes, "map.txt");
	
	EcoDriving::Parsers::Node a = nodes[138218147];

	std::cout << a.getNodeID() << std::endl;
	
	system("pause");

	return;
}