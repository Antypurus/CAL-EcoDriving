
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>

void main(void) {
	
	std::unordered_map<size_t, EcoDriving::Parsers::Way>nodes;

	EcoDriving::Linker::WayParser(nodes, "map1.txt");
	
	system("pause");

	return;
}