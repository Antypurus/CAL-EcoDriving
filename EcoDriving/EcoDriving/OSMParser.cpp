#include"OSMParser.h"

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

	}
}
