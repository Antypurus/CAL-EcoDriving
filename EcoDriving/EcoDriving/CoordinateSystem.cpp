#define USING_MATH_DEFINES

#include "CoordinateSystem.h"



CoordinateSystem::CoordinateSystem(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


CoordinateSystem::~CoordinateSystem()
{

}

double CoordinateSystem::distanceCalculation(CoordinateSystem dest)
{
	return 0.0;
}
