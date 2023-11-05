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

	//camera rotation : 
	double rotationX = 0;
	double rotationY = 0;
	double rotationZ = 0;

	
	double translationX = 0;
	double translationY = 0;
	double translationZ = 0;

	double DeltaTime = 0.0;
	double alpha = 0.0001;

	//na razie nie u¿ywana -> zamiast tego weak projection
	Vector2 PerspectiveProjection(Vector3 v)
	{
		mat4xt matProj;

		float fNear = .1f;
		float fFar = 1000.0f;
		float fFov = 45.0f; //stopnie
		float fAspectRatio = (float)800 / (float)800;
		float fFovRad = 2.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;


		Vector3 o(0, 0, 0);

		o._x = (  v._x * matProj.m[0][0] + v._y * matProj.m[1][0] + v._z * matProj.m[2][0] + matProj.m[3][0]);
		o._y = ( v._x * matProj.m[0][1] + v._y * matProj.m[1][1] + v._z * matProj.m[2][1] + matProj.m[3][1]);
		o._z = (v._x * matProj.m[0][2] + v._y * matProj.m[1][2] + v._z * matProj.m[2][2] + matProj.m[3][2]);
		float w = v._x * matProj.m[0][3] + v._y * matProj.m[1][3] + v._z * matProj.m[2][3] + matProj.m[3][3];

		if (w != 0.0f)
		{
			o._x /= w;
			o._y /= w;
			o._z /= w;
		}

		Vector2 vector2(0, 0);

		vector2._x = (400 + o._x * scale);
		vector2._y = (300 + o._y * scale);

		return vector2;
	}


	void RotateAllPointsX(double rotation)
	{
		for (int i = 0; i < points3D.size(); i++)
		{
			points3D[i].RotateX(rotation);           
		}
	}

	void RotateAllPointsY(double rotation)
	{
		for (int i = 0; i < points3D.size(); i++)
		{
			points3D[i].RotateY(rotation);
		}
	}

	void RotateAllPointsZ(float rotation)
	{
		for (int i = 0; i < points3D.size(); i++)
		{
			points3D[i].RotateZ(rotation);
		}
	}

	//Vector2 spawnPosititon = { 0, 0 };

	std::vector<Vector3> points3D;
	std::vector<Vector2> points2D;
	std::vector<Vertices> vertices;
	
	Object3D(Vector3 startPos, double scale) :
	   scale(scale)
	{

		double a = 6.0;
		points3D = {
				 Vector3{-a,-a,-a}, Vector3{-a,-a,a },
				 Vector3{a,-a, -a}, Vector3{-a, a, -a},
				 Vector3{-a,a, a}, Vector3{a, -a, a},
				 Vector3{a,a, -a}, Vector3{a, a, a}
		};

		vertices = { Vertices{0,1}, Vertices{0,2}, Vertices{0,3},
					Vertices{2,5}, Vertices{3,6}, Vertices{3,4},
					Vertices{4,7}, Vertices{6,7}, Vertices{7,5},
					Vertices{5,1}, Vertices{4,1}, Vertices{2,6}
		};

		translationX = startPos._x;
		translationY = startPos._y;
		translationZ = startPos._z;

	}

	//weak perspective projection
	Vector2 weakProjection(Vector3 v)
	{
		
		double focalLenght = 10.0;
		Vector2 v2(0, 0);

		//v2.setX(spawnPosititon.getX() + (focalLenght * v._x / (focalLenght + v._z) * scale));
		//v2.setY(spawnPosititon.getY() + (focalLenght * v._y) / (focalLenght + v._z) * scale);
	
		//       400 = windowWidth / 2 
		v2._x = (400 + (focalLenght * v._x / (focalLenght + v._z) * scale));
		v2._y = (300 + (focalLenght * v._y) / (focalLenght + v._z) * scale);
		return v2;
	}

	Vector3 ScaleVector(Vector3 v, double scale)
	{
		Vector3 scaledVector(v._x*scale, v._y*scale, v._z*scale);
	
		return scaledVector;
	}


	//display Vector 
	Vector3 startPoint3D;
	Vector3 endPoint3D;

	void Render(SDL_Renderer* renderer)
	{
		for (Vertices ver : vertices)
		{

			auto time1 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration(0);
		
			//rotating 
			points3D[ver._start].RotateX(rotationX);
			points3D[ver._start].RotateY(rotationY);
		    points3D[ver._start].RotateZ(rotationZ);
			
			points3D[ver._end].RotateX(rotationX);
			points3D[ver._end].RotateY(rotationY);
			points3D[ver._end].RotateZ(rotationZ);
			

			
			
			
			//displaying points
			startPoint3D = points3D[ver._start];
			endPoint3D = points3D[ver._end];

			startPoint3D = ScaleVector(startPoint3D, scale);
			endPoint3D = ScaleVector(endPoint3D, scale);

			startPoint3D.TranslateX(translationX);
			startPoint3D.TranslateY(translationY);
			startPoint3D.TranslateZ(translationZ);

			endPoint3D.TranslateX(translationX);
			endPoint3D.TranslateY(translationY);
			endPoint3D.TranslateZ(translationZ);
			
			//camera movement 
		
			//startPoint3D.RotateX(rotationX);
			//startPoint3D.RotateY(rotationY);

		    //endPoint3D.RotateX(rotationX);
			//endPoint3D.RotateY(rotationY);

			Vector2 startPoint2D = weakProjection(startPoint3D); Vector2 endPoint2D = weakProjection(endPoint3D);
			//Vector2 startPoint2D = PerspectiveProjection(startPoint3D); Vector2 endPoint2D = PerspectiveProjection(endPoint3D);
			
			
			
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 125);
			
			SDL_RenderDrawLine(renderer, (int)startPoint2D._x, (int)startPoint2D._y, (int)endPoint2D._x, (int)endPoint2D._y);
				
			auto time2 = std::chrono::high_resolution_clock::now();
			duration = time2 - time1;
			DeltaTime = duration.count();
			time1 = time2;

		}		
	}

	void TranslateXYZ(double x, double y, double z)
	{
		for (int i = 0; i < points3D.size(); i++)
		{
			//points3D[i].TranslateXYZ(x, y, z);
			
			translationX += x;
			translationY += y;
			translationZ += z;

		    //points3D[i].ShowXYZ();
		}
	}


	//! przeniesione do ObjectController.h !
	//! 
	//void PollEvents()
	//{
	//	SDL_Event event;

	//	if (SDL_PollEvent(&event))
	//	{
	//		switch (event.type)
	//		{
	//			//custom 
	//		case (SDL_KEYDOWN):
	//			switch (event.key.keysym.sym) {

	//			case SDLK_LEFT:
	//				TranslateXYZ(-1, 0, 0);
	//				break;

	//			case SDLK_RIGHT:
	//				TranslateXYZ(1, 0, 0);
	//				break;

	//			case SDLK_UP:
	//				TranslateXYZ(0, -1, 0);
	//				break;

	//			case SDLK_DOWN:
	//				TranslateXYZ(0, 1, 0);
	//				break;

	//			case SDLK_0:
	//				TranslateXYZ(0, 0, 1);
	//				break;

	//			case SDLK_1:
	//				TranslateXYZ(0, 0, -1);
	//				break;

	//			case SDLK_w:
	//				startPoint3D.RotateX(0.0001);
	//				endPoint3D.RotateX(0.0001);
	//				break;

	//			case SDLK_a:
	//				RotateAllPointsY(+.00001);
	//				break;

	//			case SDLK_s:
	//				//startPoint3D.RotateX(-0.0001);
	//				//endPoint3D.RotateX(-0.0001);
	//				std::cout << "CO ";
	//				break;

	//			case SDLK_d:
	//				RotateAllPointsY(-.00001);
	//				break;

	//			default:
	//				break;
	//			}
	//			break;

	//		default:
	//			break;
	//		}
	//	}
	//}

};


