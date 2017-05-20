#include "OSMParser.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <iomanip>
#include <functional>
#include <random>
#include "PROJECT_SETTINGS_MACROS.h"
#include "MATH_CONSTANTS_MACROS.h"

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

		void Conect::addEdge(const size_t srcID, const size_t dstID)
		{
			this->edges.push_back(std::make_pair(srcID, dstID));
		}
		std::vector<std::pair<size_t, size_t>> Conect::getEdges() const
		{
			return this->edges;
		}
	}
}

namespace EcoDriving {
	namespace Linker {
		void NodeParser(std::unordered_map<size_t, EcoDriving::Parsers::Node>& nodeTable, std::string filename) {
			nodeTable.clear();
			double altitude=0, longitude=0, latitude=0;
			size_t nodeID=0;
			bool hasChanged = false;
			std::string help;
			std::ifstream file(filename);
			double prevAltitude = 0;
			if (file.is_open()) {
				while (getline(file,help)) {
					static istringstream helper; helper.str(help);
					static istringstream help2;
					help2.clear();

					std::getline(helper, help, ';');
					help2.str(help);
					help2 >> nodeID;
					help2.clear();

					std::getline(helper, help, ';');
					help2.str(help);
					help2 >> latitude;
					//std::cout << "latitude:" << latitude<<endl;
					help2.clear();

					std::getline(helper, help, ';');
					help2.str(help);
					help2 >> longitude;
					//std::cout << "longitude:" << longitude << endl;
					help2.clear();

					if (!hasChanged) {
						std::random_device seedDevice;
						static std::mt19937 generator(seedDevice());
						int shouldChange = generator() % 100;
						if (shouldChange <= 100 * ELEVETAION_CHANGE_CHANCE) {
							int changeDir = generator() % 3;
							if (changeDir != 0) {
								hasChanged = true;
								double changeAmount = generator()%MAX_ELEVATION_CHANGE+1;
								if (changeDir == 1) {
									altitude = prevAltitude + changeAmount;
									prevAltitude = altitude;
								}
								else {
									altitude = prevAltitude - changeAmount;
									prevAltitude = altitude;
								}

							}
						}
					}
					else {
						hasChanged = false;
					}
#if DISPLAY_METRICS
					cout << "Altitude:" << altitude << endl;
					cout << "Latitude:" << latitude << endl;
					cout << "Longitude:" << longitude << endl;
#endif
					EcoDriving::Parsers::Node send(latitude, longitude, altitude, nodeID);
					nodeTable.insert(std::make_pair(send.getNodeID(), send));
					latitude = 0;
					nodeID = 0;
					longitude = 0;
					helper.clear();
					help2.clear();
					help.clear();
				}
			}
			else {
				std::cout << "@NodeParser:: There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
				file.close();
				return;
			}
			file.close();
			std::cout << "@NodeParser:: Parsing Of Node Information Is Complete" << std::endl;
		}

		void WayParser(std::unordered_map<size_t, EcoDriving::Parsers::Way> &wayTable, std::string filename) {
			ifstream file(filename);
			string help;
			if (file.is_open()) {
				while (getline(file,help)) {
					static int c = 0;

					string name;
					size_t wayID;
					bool isTwoWay = false;

					static istringstream help1; help1.str(help);
					static istringstream help2;
					help2.clear();

					getline(help1, help, ';');
					help2.str(help);
					help2 >> wayID;
					help2.clear();

					getline(help1, name, ';');

					if (name == "") {
						name = "Test " + to_string(c++);
					}

					getline(help1, help, ';');
					if (help == "True") {
						isTwoWay = true;
					}
					else {
						isTwoWay = false;
					}

					EcoDriving::Parsers::Way send(wayID, name, isTwoWay);
					wayTable.insert(std::make_pair(send.getWayID(), send));
					help1.clear();
					help2.clear();
					help.clear();
				}
			}
			else {
				cout << "@WayParser:: There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
				file.close();
				return;
			}
			file.close();
			std::cout << "@WayParser:: Parsing Of Way Information Is Complete" << std::endl;
		}

		void ConectParser(std::unordered_map<size_t, EcoDriving::Parsers::Conect> &conTable, std::string filename) {
			ifstream file(filename);
			string help;
			if (file.is_open()) {
				while (std::getline(file,help)) {
					size_t wayID, srcID, dstID;
					static istringstream help1; help1.str(help);
					static istringstream help2;
					help2.clear();

					getline(help1, help, ';');
					help2.str(help);
					help2 >> wayID;
					help2.clear();

					getline(help1, help, ';');
					help2.str(help);
					help2 >> srcID;
					help2.clear();

					getline(help1, help, ';');
					help2.str(help);
					help2 >> dstID;
					help2.clear();

					if (conTable.count(wayID) == 0) {
						EcoDriving::Parsers::Conect send(wayID, srcID, dstID);
						conTable.insert(std::make_pair(wayID, send));
					}
					else {
						conTable[wayID].addEdge(srcID, dstID);
					}
					help1.clear();
					help.clear();
				}
			}
			else {
				cout << "@ConnectionParser:: There Was An Issue Opening The Requested File | File is :" << filename << std::endl;
				file.close();
				return;
			}
			file.close();
			std::cout << "@ConnectionParser:: Parsing Of Node Connections Is Complete" << std::endl;
		}

		Linker::Linker() {
			std::cout << "@ParserManager:: Parsing Started" << std::endl;

			std::thread nodeParse(NodeParser, std::ref(this->nodes), NODE_FILE);
			std::thread wayParse(WayParser, std::ref(this->ways), WAY_FILE);
			std::thread conParse(ConectParser, std::ref(this->conections), NODE_CONECTIONS_FILE);

			nodeParse.join();
			wayParse.join();
			conParse.join();

			for (std::unordered_map<size_t, Parsers::Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
				locationNodes.insert(std::make_pair(it->second.getNodeID(),EcoDriving::Location::Location((it->second))));
			}

			std::random_device gen;
			std::mt19937_64 generator(gen());

			for (auto it = locationNodes.begin(); it != locationNodes.end(); ++it) {
				int a = generator() % 100;
				if (a <= 5) {
					it->second.setRecharge(true);
				}
			}

			std::cout << "@ParserManager:: Parsing  Finished" << std::endl << std::endl;
		}
	}
}