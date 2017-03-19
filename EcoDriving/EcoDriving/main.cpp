
#include"OSMParser.h"
#include<iostream>
#include<unordered_map>

void main(void) {
	
	std::unordered_map<size_t, EcoDriving::Parsers::Conect>nodes;

	EcoDriving::Linker::ConectParser(nodes, "map2.txt");
	
	system("pause");

	return;
}