#pragma once
#include "Vector2.h"
class Vector3 
{
public :	

	double _x, _y, _z;


	Vector3(double x, double y, double z) :
		_x(x), _y(y), _z(z)
	{

	}

	Vector3()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

	~Vector3()
	{
		
	}

	void ShowXYZ();

	void TranslateXYZ(double x, double y, double z)
	{
		_x += x; 
		_y += y;
		_z += z;
	}

	void TranslateX(double x)
	{
		_x += x;
	}

	void TranslateY(double y)
	{
		_y += y;
	}

	void TranslateZ(double z)
	{
		_z += z;
	}

	void ScaleX(double scale)
	{
		if(scale>0)
		_x *= scale;
	}

	void ScaleY(double scale)
	{
		if (scale > 0)
			_y *= scale;
	}

	void ScaleZ(double scale)
	{
		if (scale > 0)
			_z *= scale;
	}

	void RotateX(double rotationX)
	{
		_y = (cos(rotationX) * _y - sin(rotationX) * _z);
		_z = (sin(rotationX) * _y + cos(rotationX) * _z);
	}

	void RotateY(double rotationY)
	{
		_x = (cos(rotationY) * _x + sin(rotationY) * _z);
		_z = (-sin(rotationY) * _x + cos(rotationY) * _z);
	}

	void RotateZ(double rotationZ)
	{
		_x = (cos(rotationZ) * _x - sin(rotationZ) * _y);
		_y = (sin(rotationZ) * _x + cos(rotationZ) * _y);
	}

	static Vector3 zero()
	{
		return Vector3(0,0,0);
	}
};

