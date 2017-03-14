#include<iostream>
#include"CoordinateSystem.h"

using namespace std;

void main(void) {

	CoordinateSystem a(87.967360, 41.756192, 192), b(87.973307, 41.758701, 198);
	double dist = a.distanceCalculation(b);

	cout << "The Distance is:" << dist << endl;

	system("pause");
	return;
}