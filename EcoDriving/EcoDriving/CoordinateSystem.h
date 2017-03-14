#pragma once
class CoordinateSystem
{
public:
	double x, y, z;//Cartesian Coordinates of the object
	double latitude, longitue, altitude; //Polar Coordinates of the object
public:
	CoordinateSystem(double longitude, double latitude, double altitude,bool Cartesian);
	~CoordinateSystem();
	double distanceCalculation(CoordinateSystem dest);
};

