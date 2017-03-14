#pragma once
class CoordinateSystem
{
public:
	double x, y, z;
	CoordinateSystem(double longitude, double latitude, double altitude);
	~CoordinateSystem();
	double distanceCalculation(CoordinateSystem dest);
};


