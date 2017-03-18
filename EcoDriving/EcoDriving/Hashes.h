#pragma once 

#ifndef HASHES_H
#define HASHES_H


#include "OSMParser.h"

namespace std {

	template<>
	struct hash<EcoDriving::Parsers::Node> {
		
		size_t operator()(const EcoDriving::Parsers::Node &node)const {
			return node.getNodeID();
		}

	};

	template<>
	struct hash<EcoDriving::Parsers::Way> {

		size_t operator()(const EcoDriving::Parsers::Way &way)const {
			return way.getWayID();
		}

	};

	template<>
	struct hash<EcoDriving::Parsers::Conect> {

		size_t operator()(const EcoDriving::Parsers::Conect &conect)const {
			return conect.getWayID();
		}

	};
}
#endif // !HASHES_H