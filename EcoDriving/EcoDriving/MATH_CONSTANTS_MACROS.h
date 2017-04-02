#pragma once


#define EARTH_RADIUS 6370000 // this macro represents the earths radius from its core to sea level

#define UP_HILL_ENERGY_COST 1.5 // this macro represents the amount of energy per meter the car has to spend to go up a hill on Watt/Meter
#define FLAT_ENERGY_COST 1 // this macro represents the amount of energy per meter the car has to spend to move in a surface with uniform elevation in Watt/Meter
#define DOWN_HILL_REFENERATION 0.5 // this macro represents the amount of energy per meter the car regenerates while going down a hill in Watt/Meter

#define ELEVETAION_CHANGE_CHANCE 0.05 // this macro represents the change of there being a change in elevation while generating the altitudes for the various nodes
#define MAX_ELEVATION_CHANGE 200;