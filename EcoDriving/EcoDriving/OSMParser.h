#pragma once

#include<unordered_map>

namespace EcoDriving {

	namespace Parsers {

		class Node {
		private:
			double latitude;
			double longitude;
			double altitude;
			size_t nodeID;
		public:
			Node(double latitude, double longitude, double altitude, size_t nodeID);
			Node() {};
			size_t getNodeID()const;
			double getAltitude()const;
			double getLongitude()const;
			double getLatitude()const;
			bool operator==(const Node &node)const;
		};

		class Way {
		private:
			std::string name;
			size_t wayID;
			bool twoWay = false;
		public:
			Way(size_t wayID, std::string name, bool isTwoWay);
			std::string getName()const;
			size_t getWayID()const;
			bool isTwoWay()const;
			bool operator==(const Way &way)const;
		};

		class Conect {
		private:
			size_t wayID;
			size_t srcID;
			size_t dstID;
		public:
			Conect(size_t wayID, size_t srcID, size_t dstID);
			size_t getWayID()const;
			size_t getSrcID()const;
			size_t getDstID()const;
			bool operator==(const Conect &conect)const;
		};

	}

}

#include"Hashes.h"
#include"Location.h"

namespace EcoDriving {

	namespace Linker {

		void NodeParser(std::unordered_map<size_t,EcoDriving::Parsers::Node> &nodeTable, std::string filename);
		void WayParser(std::unordered_map<size_t,EcoDriving::Parsers::Way> &wayTable, std::string filename);
		void ConectParser(std::unordered_map<size_t,EcoDriving::Parsers::Conect> &conTable, std::string filename);

		class Linker{
		public:
			std::unordered_map<size_t,Parsers::Node> nodes;
			std::unordered_map<size_t,Parsers::Way> ways;
			std::unordered_map<size_t,Parsers::Conect> conections;
			std::unordered_map<size_t,Location::Location> locationNodes;

			Linker();
		};
	
	}
}
