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
		public:
			uint64_t getID()const{
				return nodeID;
			}
		};


		void OSMNodeParser(std::unordered_set<OSMNode> &hash_table, std::string filename);

		class OSMWays {
		private:
			uint64_t wayID;
			std::string wayName = "";
			bool twoWay = false;
		public:
			uint64_t getID()const{
				return wayID;
			}
		};

		void OSMWaysParse(std::unordered_set<OSMWays> &hash_table, std::string filename);

		class OSMConections {
		private:
			uint64_t wayID;
			uint64_t sourceNodeID;
			uint64_t destinationNodeID;
		public:
			uint64_t getID()const {
				return wayID;
			}
			uint64_t getSrcID()const {
				return sourceNodeID;
			}
			uint64_t getDestID()const {
				return destinationNodeID;
			}
		};

		void OSMConectionsParse(std::unordered_set<OSMConections> &hash_table, std::string filename);
	}

		namespace Linker {

			class OSMParserLinker {
			private:
				std::unordered_set<Parser::OSMNode> nodes;
				std::unordered_set<Parser::OSMWays> ways;
				std::unordered_set<Parser::OSMConections> conections;
			};
		}
	
}

namespace std {

	template<>
	struct hash<EcoDriving::Parser::OSMNode> {

		size_t operator()(EcoDriving::Parser::OSMNode const &node) const noexcept {
			return node.getID();
		}
	};

}

