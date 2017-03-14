#pragma once

#include"CoordinateSystem.h"

class ElectricVehicle
{
private:
	CoordinateSystem CurrentPosition;
	double AverageVelocity; //average velocity the car moves at
	double BatteryCapacity; //Battery capacity in watt
	double RiseEnergySpent = 1.5; //watt per meter spent to go up a hill
	double PlanarEnergySpent = 1; // watt per meter spent while traveling on a flat surface
	double RollEnergySpent = 0.5; //watt recovered while going down a hill
public:
	ElectricVehicle();
	~ElectricVehicle();
};

