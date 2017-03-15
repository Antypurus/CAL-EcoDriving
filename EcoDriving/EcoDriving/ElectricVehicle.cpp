#include "ElectricVehicle.h"

namespace EcoDriving {
	namespace EcoVehicle {
		/*
		Parameter:
			dobule x - Represents the cars x coordinate , using cartesian coordinates
			double y - Represents the cars y coordinate , using cartesian coordinates
			double z - Represents the cars z coordinate , using cartesian coordinates
			double AvgVelocity - Represents the average velocity the car will be moving at
			doublw BatteryCapacity - Represents the total value of energy in Watt the cars battery can store

		Description:
			This is the constructor and merely assignes the value of each member,that needs a value to be passed in.
		*/

		ElectricVehicle::ElectricVehicle(double x, double y, double z, double AvgVelocity, double BatteryCapacity)
		{
			this->CurrentPosition = new EcoDriving::EcoCoordinate::CoordinateSystem(x, y, z, true);
			this->AverageVelocity = AvgVelocity;
			this->BatteryCapacity = BatteryCapacity;
			this->CurrentBatteryAmmount = BatteryCapacity;
		}


		ElectricVehicle::~ElectricVehicle()
		{
		}
	}
}