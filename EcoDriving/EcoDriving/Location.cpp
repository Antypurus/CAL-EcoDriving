#include "Location.h"
#include"OSMParser.h"
#include"CoordinateSystem.h"
#include <iostream>
#include "MATH_CONSTANTS_MACROS.h"


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

		double Location::weightTo(const Location &loc) {
			double dist = this->getCoordinates().distanceCalculation(loc.getCoordinates());
			if (this->getCoordinates().z > loc.getCoordinates().z) {
				return (dist - dist*DOWN_HILL_REFENERATION);
			}
			else if (this->getCoordinates().z < loc.getCoordinates().z) {
				return dist*UP_HILL_ENERGY_COST;
			}
			else {
				return dist*FLAT_ENERGY_COST;
			}
			return dist;
		}
	}
}