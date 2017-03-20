#include "Location.h"


namespace EcoDriving {
	namespace Location {

		Location::Location(const EcoDriving::Parsers::Node &node)
		{
			this->m_Coordinates = new EcoCoordinate::CoordinateSystem(node.getLongitude(), node.getLatitude(), node.getAltitude(), false);
			this->m_HasRechargeStation = false;
			this->m_NodeID = node.getNodeID();
		}

		Location::Location(const EcoDriving::Parsers::Node &node, bool hasRechargeStation)
		{
			this->m_Coordinates = new EcoCoordinate::CoordinateSystem(node.getLongitude(), node.getLatitude(), node.getAltitude(), false);
			this->m_HasRechargeStation = hasRechargeStation;
			this->m_NodeID = node.getNodeID();
		}

		void Location::setName(std::string name)
		{
			this->m_LocationName = name;
		}

		std::string Location::getName()const {
			return this->m_LocationName;
		}

		size_t Location::getNodeID()const {
			return this->m_NodeID;
		}

		EcoCoordinate::CoordinateSystem Location::getCoordinates() const
		{
			return *(this->m_Coordinates);
		}
	}
}