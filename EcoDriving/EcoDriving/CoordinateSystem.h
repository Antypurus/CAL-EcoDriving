#pragma once
class CoordinateSystem
{
public:
	double x, y, z;
	CoordinateSystem(double x,double y,double z);
	~CoordinateSystem();
	double distanceCalculation(CoordinateSystem dest);
};

