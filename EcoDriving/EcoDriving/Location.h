#pragma once
#include<string>



namespace EcoDriving {
	namespace Parsers {
		class Node;//forward declare of de node class
	}

	namespace EcoCoordinate {
		class CoordinateSystem;//forward declare of the Coordinate System class
	}

	namespace Location {
		class Location
		{
		private:
			size_t m_NodeID;
			EcoCoordinate::CoordinateSystem *m_Coordinates;
			std::string m_LocationName;
			bool m_HasRechargeStation=false;
		public:
			Location(const EcoDriving::Parsers::Node &node);
			Location();
			Location(const Parsers::Node &node,bool hasRechargeStation);
			void setName(std::string name);
			std::string getName()const;
			size_t getNodeID()const;
			EcoCoordinate::CoordinateSystem getCoordinates()const;
			bool operator==(const Location &loc)const;
			void operator=(const Location &loc);
			bool operator!=(const Location &loc)const {
				if (this->m_NodeID != loc.getNodeID()) {
					return true;
				}
				return false;
			}
			void setRecharge(bool value) {
				this->m_HasRechargeStation = value;
			}
			bool getRecharge() {
				return this->m_HasRechargeStation;
			}
		};
	}
}

