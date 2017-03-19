#include"OSMParser.h"
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include<thread>
#include<unordered_map>

using namespace std;

namespace EcoDriving {
	namespace Parsers {
		//Node	
		size_t Node::getNodeID()const {
			return this->nodeID;
		}

		double Node::getAltitude()const {
			return this->altitude;
		}

		double Node::getLatitude()const {
			return this->latitude;
		}

		double Node::getLongitude()const {
			return this->longitude;
		}

		bool Node::operator==(const Node &node)const {
			return (this->nodeID == node.getNodeID());
		}

		Node::Node(double latitude, double longitude, double altitude, size_t nodeID) {
			this->altitude = altitude;
			this->latitude = latitude;
			this->longitude = longitude;
			this->nodeID = nodeID;
		}

		//Way

		std::string Way::getName()const {
			return this->name;
		}

		size_t Way::getWayID()const {
			return this->wayID;
		}

		bool Way::isTwoWay()const {
			return this->twoWay;
		}

		bool Way::operator==(const Way &way)const {
			return (this->wayID == way.getWayID());
		}

		Way::Way(size_t wayID, std::string name, bool isTwoWay) {
			this->wayID = wayID;
			this->name = name;
			this->twoWay = isTwoWay;
		}

		//Conect

		size_t Conect::getWayID()const {
			return this->wayID;
		}

		size_t Conect::getDstID()const {
			return this->dstID;
		}

		size_t Conect::getSrcID()const {
			return this->srcID;
		}

		bool Conect::operator==(const Conect &conect)const {
			return (this->wayID == conect.getWayID());
		}

		Conect::Conect(size_t wayID, size_t srcID, size_t dstID) {
			this->wayID = wayID;
			this->srcID = srcID;
			this->dstID = dstID;
		}

	}
}

namespace EcoDriving {
	namespace Linker {
		void NodeParser(std::unordered_map<size_t, EcoDriving::Parsers::Node>& nodeTable, std::string filename) {

			nodeTable.clear();

			double altitude, longitude, latitude;
			size_t ID;

			std::string help;
			std::ifstream file(filename);

			if (file.is_open()) {
				while (!file.eof()) {
					double latitude = 0, longitude = 0, altitude = 0;
					size_t nodeID = 0;

					help = "";

					std::getline(file, help);

					stringstream helper(help);
					stringstream help2;

					std::getline(helper, help, ';');
					help2 << help;
					help2 >> nodeID;

					std::getline(helper, help, ';');
					help2 << help;
					help2 >> latitude;

					std::getline(helper, help, ';');
					help2 << help;
					help2 >> longitude;

					EcoDriving::Parsers::Node send(latitude, longitude, altitude, nodeID);

					nodeTable.insert(std::make_pair(send.getNodeID(), send));
				}
			}
			else {
				std::cout << "There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
			}
			file.close();

			std::cout << "Parsing Of Node Information Is Complete" << std::endl;

		}

		void WayParser(std::unordered_map<size_t, EcoDriving::Parsers::Way> &wayTable, std::string filename) {
			ifstream file(filename);
			if (file.is_open()) {
				while (!file.eof()) {
					string name;
					size_t wayID;
					bool isTwoWay = false;

					string help;
					stringstream help1, help2;
					getline(file, help);
					help1 << help;
					help = "";


					getline(help1, help, ';');
					help2 << help;
					help2 >> wayID;

					getline(help1, name, ';');

					getline(help1, help, ';');
					if (help == "True") {
						isTwoWay = true;
					}
					else {
						isTwoWay = false;
					}

					EcoDriving::Parsers::Way send(wayID, name, isTwoWay);

					wayTable.insert(std::make_pair(send.getWayID(), send));
				}
			}
			else {
				cout << "There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
			}
			file.close();
			std::cout << "Parsing Of Way Information Is Complete" << std::endl;
		}

		void ConectParser(std::unordered_map<size_t, EcoDriving::Parsers::Conect> &conTable, std::string filename) {
			ifstream file(filename);
			if (file.is_open()) {
				while (!file.eof()) {
					size_t wayID, srcID, dstID;
					string help;
					stringstream help1, help2;

					getline(file, help);
					help1 << help;

					getline(help1, help, ';');
					help2 << help;
					help2 >> wayID;

					getline(help1, help, ';');
					help2 << help;
					help2 >> srcID;

					getline(help1, help, ';');
					help2 << help;
					help2 >> dstID;

					EcoDriving::Parsers::Conect send(wayID, srcID, dstID);

					conTable.insert(std::make_pair(wayID, send));
				}
			}
			else {
				cout << "There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
			}
			file.close();
			std::cout << "Parsing Of Node Conections Is Complete" << std::endl;
		}

		Linker::Linker() {
			std::cout << "Parsing Started" << std::endl;

			std::thread nodeParse(NodeParser, this->nodes,"map.txt");
			std::thread wayParse(WayParser, this->ways, "map1.txt");
			std::thread conParse(ConectParser, this->conections, "map2.txt");

			nodeParse.join();
			wayParse.join();
			conParse.join();

			std::cout << "Parsing  Finished" << std::endl;
		}
	}
}
