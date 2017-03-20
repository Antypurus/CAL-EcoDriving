#pragma once
#include"CoordinateSystem.h"
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
			Location();
			~Location();
		};
	}
}

