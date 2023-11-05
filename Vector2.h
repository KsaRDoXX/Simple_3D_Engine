#pragma once
#include <iostream>
class Vector2
{
public : 
	Vector2(double x, double y):
		_x(x),_y(y){}

	~Vector2()
	{

	}
	
	double _x, _y;

	void ShowXY()
	{
		std::cout << "V2 : x =" << _x << ", y =" << _y << "\n";
	}

protected : 
	

};

