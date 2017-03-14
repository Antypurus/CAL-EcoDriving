#define _USE_MATH_DEFINES

#include "CoordinateSystem.h"
#include <cmath>

/*
Parameter:
	double longitude_x - 
	double latitude_y - 
	double altitude_z -
	bool Cartesian -

Description:
	This Member-Fucntion 
*/

CoordinateSystem::CoordinateSystem(double longitude_x, double latitude_y, double altitude_z,bool Cartesian)
{
	if (Cartesian) {
		double earthRadius = 6370000;

		longitude_x = longitude_x * M_PI / 180.0;
		latitude_y = latitude_y * M_PI / 180.0;

		this->x = (altitude_z + earthRadius)*cos(latitude_y)*sin(longitude_x);
		this->y = (altitude_z + earthRadius)*sin(latitude_y);
		this->z = (altitude_z + earthRadius)*cos(latitude_y)*cos(longitude_x);
	}else {
		this->x = longitude_x;
		this->y = latitude_y;
		this->z = altitude_z;
	}
}


CoordinateSystem::~CoordinateSystem()
{

}

double CoordinateSystem::distanceCalculation(CoordinateSystem dest)
{
	return sqrt(pow(dest.x-x,2)+ pow(dest.y - y, 2) + pow(dest.z - z, 2));
}
