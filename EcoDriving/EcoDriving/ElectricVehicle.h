#pragma once
#include"MATH_CONSTANTS_MACROS.h"

namespace EcoDriving {
	namespace EcoCoordinate {
		class CoordinateSystem;
	}
}

namespace EcoDriving {
	namespace EcoVehicle {
		/*
			This class represents an electrical vehicle to used to obtain values in the graph calculations
		*/
		class ElectricVehicle
		{
		private:
			EcoDriving::EcoCoordinate::CoordinateSystem *CurrentPosition; //represents the cars currente position
			double AverageVelocity; //average velocity the car moves at in meters/sec
			double BatteryCapacity; //Battery capacity in watt
			double CurrentBatteryAmmount; //Ammount of energy in Watt currently available in the cars battery
			double RiseEnergySpent = UP_HILL_ENERGY_COST; //watt per meter spent to go up a hill
			double PlanarEnergySpent = FLAT_ENERGY_COST; // watt per meter spent while traveling on a flat surface
			double RollEnergySpent = DOWN_HILL_REFENERATION; //watt recovered while going down a hill
		public:
			ElectricVehicle(double x, double y, double z, double AvgVelocity, double BatteryCapacity);
			~ElectricVehicle();
			double wouldSpend(EcoCoordinate::CoordinateSystem placeToMove)const;
			void moveTo(EcoCoordinate::CoordinateSystem placeToMove);
			double timeTo(EcoCoordinate::CoordinateSystem placeToMove);
		};

	}
}

