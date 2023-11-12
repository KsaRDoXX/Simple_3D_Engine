#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vertices.h"
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Vector2.h"
#include "Vector3.h"
#include <math.h>
#include <chrono>


struct mat4xt
{
	double m[4][4] = { 0 }; //<- Macierz : row, column
};

class Object3D
{
public:
	double scale = 100;

	//dlugosc boku
	double a = 100.0;


	std::vector<Vector3> modelSpacePoints3D;
	std::vector<Vector3> worldSpacePoints3D;

	std::vector<Vector2> points2D;
	std::vector<Vertices> vertices;

	//na razie nie u¿ywana -> zamiast tego weak projection
	Vector2 PerspectiveProjection(Vector3 v);

	//weak perspective projection
	Vector2 weakProjection(Vector3 v);

	double rotationX = 0;
	double rotationY = 0;
	double rotationZ = 0;
	
	double translationX = 0;
	double translationY = 0;
	double translationZ = 0;

	double DeltaTime = 0.0;
	double alpha = 0.0001;

	//Physics
	double speedX = 0.0;
	double speedY = 0.0;
	double speedZ = 0.0;

	double accelerationX = 0.0;
	double accelerationY = 0.0;
	double accelerationZ = 0.0;

	double mass = 10.0;

	//œrednia punktów DisplayPoints3D 
	//Vector3 massCenter = Vector3(a/2,a/2,a/2);
	Vector3 massCenter = averagePoint(worldSpacePoints3D);

	//applies rotation to model space points
	void RotateAllPointsX(double rotation);
	void RotateAllPointsY(double rotation);
	void RotateAllPointsZ(double rotation);

	//aplies translation to world space points
	void TranslateAllWorldPoints();

	//changes values of translateX/Y/Z
	void TranslateXYZ(double x, double y, double z);
	
	Object3D(Vector3 startPos, double scale);

	Vector3 ScaleVector(Vector3 v, double scale);
	Vector3 averagePoint(std::vector<Vector3> vectors);

	//display Vector 
	Vector3 startPoint3D;
	Vector3 endPoint3D;

	//to improve
	void Render(SDL_Renderer* renderer);
	
};


