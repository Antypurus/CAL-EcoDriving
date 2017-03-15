#pragma once

#include<stdint.h>
#include<unordered_set>

namespace EcoDriving {
	namespace Parser {

		class OSMNode {
		public:
			double latitude;
			double longitude;
			double altitude;
			uint64_t nodeID;
		};

		void OSMNodeParser(std::unordered_set<OSMNode> &hash_table);

		class OSMWays {

		};

		void OSMWaysParse(std::unordered_set<OSMWays> &hash_table);

		class OSMConections {

		};

		void OSMConectionsParse(std::unordered_set<OSMConections> &hash_table);

	}
}

