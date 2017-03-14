#define _USE_MATH_DEFINES

#include "CoordinateSystem.h"
#include <cmath>



CoordinateSystem::CoordinateSystem(double longitude, double latitude, double altitude)
{

	double earthRadius = 6370000;

	longitude = longitude * M_PI / 180.0;
	latitude = latitude * M_PI / 180.0;
	
	this->x = (altitude + earthRadius)*cos(latitude)*sin(longitude);
	this->y = (altitude + earthRadius)*sin(latitude);
	this->z = (altitude + earthRadius)*cos(latitude)*cos(longitude);
}


CoordinateSystem::~CoordinateSystem()
{

}

double CoordinateSystem::distanceCalculation(CoordinateSystem dest)
{
	return sqrt(pow(dest.x - x, 2) + pow(dest.y - y, 2) + pow(dest.z - z, 2));
}
