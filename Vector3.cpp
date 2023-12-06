#include "Vector3.h"
#include <iostream>



void Vector3::ShowXYZ()
{
	std::cout << "x =" << _x << ", y =" << _y << ", z ="<< _z <<"\n";
}

std::vector<Vector3> Vector3::vectorRepresentation(Vector3 drivingPoint, double scale)
{   
	std::vector<Vector3> startEndPoints;

		Vector3 startPoint = drivingPoint;
		Vector3 endPoint;
		
		endPoint._x = startPoint._x + (this->_x) * scale;
		endPoint._y = startPoint._y + (this->_y) * scale;
		endPoint._z = startPoint._z + (this->_z) * scale;
		
	
		startEndPoints.emplace_back(startPoint);
		startEndPoints.emplace_back(endPoint);

		return startEndPoints;
}