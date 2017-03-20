#pragma once
#include"CoordinateSystem.h"
#include"OSMParser.h"
#include<string>

namespace EcoDriving {
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
			Location(const EcoDriving::Parsers::Node &node,bool hasRechargeStation);
			void setName(std::string name);
			std::string getName()const;
			size_t getNodeID()const;
			EcoCoordinate::CoordinateSystem getCoordinates()const;
		};
	}
}

