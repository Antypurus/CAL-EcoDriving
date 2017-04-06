#define _USE_MATH_DEFINES

#include "CoordinateSystem.h"
#include <cmath>
#include "MATH_CONSTANTS_MACROS.h"

namespace EcoDriving {
	namespace EcoCoordinate {
		/*
		Parameter:
			double longitude_x - longitude if the coordinates are polar , or x axis value if coordinates are cartesian
			double latitude_y - latitude if the coordinates are polar , or y axis value if coordinates are cartesian
			double altitude_z -altitude if the coordinates are polar , or z axis value if coordinates are cartesian,this value does not need to take the
			the earths radius into account as the function already does that on its own.
			bool Cartesian - this bool indicates if the passed coordinates are cartesian or polar , cartesian if this is true and polar if false

		Description:
			This Member-Fucntion is the constructor and if the coordinates are cartesian it saves those value and from them calculates the polar coordinates
			if the coodinates are polar it calculates the cartesian coordinates from those polar coordinates and saves the values.The earths radius is taken
			into account by the function , the earths radius is defined as a macro in the MATH_CONSTANTS_MACROS.h file
		*/

		CoordinateSystem::CoordinateSystem(double longitude_x, double latitude_y, double altitude_z,const bool Cartesian)
		{
			if (!Cartesian) {
				this->altitude = altitude_z;
				this->longitue = longitude_x;
				this->latitude = latitude_y;
				longitude_x = longitude_x * M_PI / 180.0;//converting longitude polar coordinte from degrees to radians
				latitude_y = latitude_y * M_PI / 180.0;//converting latitude polar coordinte from degrees to radians
				/*
				these are formulas for calculating a set of cartesian coordinates given a set o porlar coodinates , these formulas assume that earth is a perfect sphere as for small distances this will generate a very small error , take into consideration that earth is nor a perfect sphere but an eliptic sphere therefore these formulas would generate a large error for very large distances like maybe inter country distance.
				*/
				this->x = (altitude_z + EARTH_RADIUS)*cos(latitude_y)*sin(longitude_x);
				this->y = (altitude_z + EARTH_RADIUS)*sin(latitude_y);
				this->z = (altitude_z + EARTH_RADIUS)*cos(latitude_y)*cos(longitude_x);
			}
			else {
				this->x = longitude_x;
				this->y = latitude_y;
				this->z = altitude_z;
			}
		}

		/*
			The destructor does not have a distinc behavior from the dafault behavior , and its definition was added duo to Visual Studios Class Generation system
		*/
		CoordinateSystem::~CoordinateSystem()
		{

		}


		/*
		Parameters:
			- CoordinateSystem dest - point to witch the currents points distance wants to be calculated

		Description:
			This method receives a point and will calculate this points distance to the passed point , for this it will simply use the formula for calculating distance in cartesian spaces ;
			d = sqrt((x1-x2)^2+(y1-y2)^2+(z1-z2)^2) , also knows as the formula for calculating the euclidean distance between two points.
		*/
		double CoordinateSystem::distanceCalculation(const CoordinateSystem &dest)const
		{
			return (sqrt(pow(dest.x - x, 2) + pow(dest.y - y, 2) + pow(dest.z - z, 2)));
		}
	}
}