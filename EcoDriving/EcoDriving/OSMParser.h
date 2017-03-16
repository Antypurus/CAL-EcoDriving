#pragma once

#include<stdint.h>
#include<unordered_set>

namespace EcoDriving {
	namespace Parser {

		class OSMNode {
		private:
			double latitude;
			double longitude;
			double altitude;
			uint64_t nodeID;
		};

		void OSMNodeParser(std::unordered_set<OSMNode> &hash_table,std::string filename);

		class OSMWays {
		private:
			uint64_t wayID;
			std::string wayName = "";
			bool twoWay = false;
		};

		void OSMWaysParse(std::unordered_set<OSMWays> &hash_table, std::string filename);

		class OSMConections {
		private:
			uint64_t wayID;
			uint64_t sourceNodeID;
			uint64_t destinationNodeID;
		};

		void OSMConectionsParse(std::unordered_set<OSMConections> &hash_table, std::string filename);

		namespace Linker {

			class OSMParserLinker {
			private:
				std::unordered_set<OSMNode> nodes;
				std::unordered_set<OSMWays> ways;
				std::unordered_set<OSMConections> conections;
			};
		}

	}
}

