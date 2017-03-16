#pragma once

namespace EcoDriving {
	namespace EcoCoordinate {
		/*
		this class represents a coordinate system that contains at least a set of x,y and z cartesian coordinates , it might also have polar coordinates
		*/
		class CoordinateSystem
		{
		public:
			double x, y, z;//Cartesian Coordinates of the object
			double latitude, longitue, altitude; //Polar Coordinates of the object
		public:
			CoordinateSystem(double longitude, double latitude, double altitude, bool Cartesian);
			~CoordinateSystem();
			inline double distanceCalculation(CoordinateSystem dest);
		};
	}
}


