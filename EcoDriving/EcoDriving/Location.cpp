#include "Location.h"
#include"OSMParser.h"
#include"CoordinateSystem.h"
#include <iostream>


namespace EcoDriving {
	namespace Location {

		Location::Location(const EcoDriving::Parsers::Node &node)
		{
			this->m_Coordinates = new EcoCoordinate::CoordinateSystem(node.getLongitude(), node.getLatitude(), node.getAltitude(), false);
			this->m_HasRechargeStation = false;
			this->m_NodeID = node.getNodeID();
			//std::cout <<"Location"<<this->m_Coordinates->x << std::endl;
		}

		Location::Location()
		{
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
		bool Location::operator==(const Location & loc) const
		{
			if (this->m_NodeID == loc.getNodeID()) {
				return true;
			}
			return false;
		}

		void Location::operator=(const Location &loc) {
			this->m_Coordinates = &(loc.getCoordinates());
			this->m_NodeID = loc.getNodeID();
		}
	}
}