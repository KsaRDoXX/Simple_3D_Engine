//#pragma once
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vertices.h"
//#include <iostream>
//#include <vector>
//#include "SDL.h"
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Object3D.h"
//
//class Cube
//{
//public:
//	float scale = .001f;
//	float rotation = 0;
//	float rotationX = 0;
//	float rotationY = 0;
//
//	Vector2 PerspectiveProjection(Vector3 v)
//	{
//		mat4xt matProj;
//
//		float fNear = .1f;
//		float fFar = 1000.0f;
//		float fFov = 10.0f; //stopnie
//		float fAspectRatio = (float)800 / (float)800;
//		float fFovRad = 2.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
//
//		matProj.m[0][0] = fAspectRatio * fFovRad;
//		matProj.m[1][1] = fFovRad;
//		matProj.m[2][2] = fFar / (fFar - fNear);
//		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
//		matProj.m[2][3] = 1.0f;
//		matProj.m[3][3] = 0.0f;
//
//
//		Vector3 o(0, 0, 0);
//
//		o.setX(v.getX() * matProj.m[0][0] + v.getY() * matProj.m[1][0] + v.getZ() * matProj.m[2][0] + matProj.m[3][0]);
//		o.setY(v.getX() * matProj.m[0][1] + v.getY() * matProj.m[1][1] + v.getZ() * matProj.m[2][1] + matProj.m[3][1]);
//		o.setZ(v.getX() * matProj.m[0][2] + v.getY() * matProj.m[1][2] + v.getZ() * matProj.m[2][2] + matProj.m[3][2]);
//		float w = v.getX() * matProj.m[0][3] + v.getY() * matProj.m[1][3] + v.getZ() * matProj.m[2][3] + matProj.m[3][3];
//
//		if (w != 0.0f)
//		{
//			o.setX(o.getX() / w); o.setY(o.getY() / w); o.setZ(o.getZ() / w);
//		}
//
//		//Zwracanie 2 wymiar
//		Vector2 vector2(0, 0);
//
//		vector2.setX(o.getX() * scale);
//		vector2.setY(o.getY() * scale);
//
//		return vector2;
//	}
//
//	Vector3 RotateX(Vector3 v3, int direction)
//	{
//		Vector3 rotatedPoint(v3.getX(), 0, 0);
//		rotationX += 0.0001f * direction;
//
//		rotatedPoint.setY((cos(rotationX) * v3.getY() - sin(rotationX) * v3.getZ()));
//		rotatedPoint.setZ((sin(rotationX) * v3.getY() + cos(rotationX) * v3.getZ()));
//
//		return rotatedPoint;
//
//	}
//
//	Vector3 RotateY(Vector3 v3, int direction)
//	{
//		rotationY += 0.0001f;
//		Vector3 rotatedPoint(0, v3.getY(), 0);
//
//		rotatedPoint.setX(cos(rotationY) * v3.getX() + sin(rotationY) * v3.getZ());
//		rotatedPoint.setZ((-sin(rotationY) * v3.getX() + cos(rotationY) * v3.getZ()));
//
//		return rotatedPoint;
//	}
//
//	Vector3 RotateZ(Vector3 v3, int direction)
//	{
//		Vector3 rotatedPoint(0, 0, v3.getZ());
//
//		rotatedPoint.setX(cos(rotation) * v3.getX() - sin(rotation) * v3.getY());
//		rotatedPoint.setY(sin(rotation) * v3.getX() + cos(rotation) * v3.getY());
//
//		return rotatedPoint;
//	}
//
//	Vector2 spawnPosititon = { 400, 300 };
//
//	std::vector<Vector3> points3D;
//	std::vector<Vector2> points2D;
//	std::vector<Vertices> vertices;
//
//	Cube(Vector2 startPos, float scale) :
//		spawnPosititon(startPos), scale(scale)
//	{
//
//
//		/*points3D = {
//				 Vector3{-1.0f,-1.0f,-1.0f}, Vector3{-1.0f,-1.0f,1.0f },
//				 Vector3{1.0f,-1.0f, -1.0f}, Vector3{-1.0f, 1.0f, -1.0f},
//				 Vector3{-1.0f,1.0f, 1.0f}, Vector3{1.0f, -1.0f, 1.0f},
//				 Vector3{1.0f,1.0f, -1.0f}, Vector3{1.0f, 1.0f, 1.0f}
//		};*/
//
//		//size
//		
//		float a = 6.0f;
//		points3D = {
//				 Vector3{-a,-a,-a}, Vector3{-a,-a,a },
//				 Vector3{a,-a, -a}, Vector3{-a, a, -a},
//				 Vector3{-a,a, a}, Vector3{a, -a, a},
//				 Vector3{a,a, -a}, Vector3{a, a, a}
//		};
//
//		//przesuniêcie w osi Z przy starcie
//
//		float translationZ = 0.0f;
//		for (int i = 0; i < points3D.size(); i++)
//		{
//			points3D[i].setZ(points3D[i].getZ() + translationZ);
//		}
//
//
//
//
//		vertices = { Vertices{0,1}, Vertices{0,2}, Vertices{0,3},
//					Vertices{2,5}, Vertices{3,6}, Vertices{3,4},
//					Vertices{4,7}, Vertices{6,7}, Vertices{7,5},
//					Vertices{5,1}, Vertices{4,1}, Vertices{2,6}
//		};
//	}
//
//	//weak perspective projection
//	Vector2 weakProjection(Vector3 v)
//	{
//		float FOV = 10.0f;
//		Vector2 v2(0, 0);
//
//		v2.setX(spawnPosititon.getX() + (FOV * v.getX()) / (FOV + v.getZ()) * scale);
//		v2.setY(spawnPosititon.getY() + (FOV * v.getY()) / (FOV + v.getZ()) * scale);
//
//		return v2;
//	}
//
//	void Render(SDL_Renderer* renderer)
//	{
//		for (Vertices ver : vertices)
//		{
//			//rotation += 0.00001;
//			//weak perspective projection :
//
//		//	Vector3 rotatedStartPoint = RotateX((points3D[ver._start]));
//			//Vector3 rotatedEndPoint = RotateX((points3D[ver._end]));
//			
//			Vector3 rotatedStartPoint = (points3D[ver._start]);
//			Vector3 rotatedEndPoint = (points3D[ver._end]);
//
//
//			//without rotation :
//			//Vector2 start = weakProjection(rotatedStartPoint); Vector2 end = weakProjection(rotatedEndPoint);
//			//Vector2 start = PerspectiveProjection(rotatedStartPoint); Vector2 end = PerspectiveProjection(rotatedEndPoint);
//		
//			//with rotation
//			
//			//Vector2 start = PerspectiveProjection(points3D[ver._start]); Vector2 end = PerspectiveProjection(points3D[ver._end]);		
//			Vector2 start = weakProjection(points3D[ver._start]); Vector2 end = weakProjection(points3D[ver._end]);
//			
//			
//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 125);
//			SDL_RenderDrawLine(renderer, start.getX(), start.getY(), end.getX(), end.getY());
//
//
//		}
//		SDL_RenderPresent(renderer);
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//		SDL_RenderClear(renderer);
//	}
//
//	void TranslateXYZ(float x, float y, float z)
//	{
//		for (int i = 0; i < points3D.size(); i++)
//		{
//			points3D[i].TranslateXYZ(x, y, z);
//			points3D[i].ShowXYZ();
//		}
//	}
//
//	void RotateAllPointsX(int direction)
//	{
//		for (int i = 0; i < points3D.size(); i++)
//		{
//			points3D[i] = RotateX(points3D[i], direction);
//			points3D[i].ShowXYZ();
//
//		}
//	}
//
//	void RotateAllPointsY(int direction)
//	{
//		for (int i = 0; i < points3D.size(); i++)
//		{
//			points3D[i] = RotateY(points3D[i], direction);
//			points3D[i].ShowXYZ();
//		}
//	}
//
//	void RotateAllPointsZ(int direction)
//	{
//		for (int i = 0; i < points3D.size(); i++)
//		{
//			points3D[i] = RotateY(points3D[i], direction);
//			points3D[i].ShowXYZ();
//
//		}
//	}
//
//
//	
//	void PollEvents()
//	{
//		SDL_Event event;
//
//		if (SDL_PollEvent(&event))
//		{
//			switch (event.type)
//			{
//				//custom 
//			case (SDL_KEYDOWN):
//				switch (event.key.keysym.sym) {
//				case SDLK_LEFT:
//					TranslateXYZ(-1,0,0);
//					break;
//
//				case SDLK_RIGHT:
//					
//					TranslateXYZ(1, 0, 0);
//					break;
//
//				case SDLK_UP:
//					TranslateXYZ(0, -1, 0);
//					break;
//
//				case SDLK_DOWN:
//					TranslateXYZ(0, 1, 0);
//					break;
//
//				case SDLK_0:
//					TranslateXYZ(0, 0, 1);
//					break;
//
//				case SDLK_1:
//					TranslateXYZ(0, 0, -1);
//					break;
//
//				case SDLK_w : 
//					RotateAllPointsX(-1);
//					break;
//				case SDLK_a:
//					RotateAllPointsY(+1);
//					break;
//				case SDLK_s:
//					RotateAllPointsX(+1);
//					break;
//				case SDLK_d:
//					RotateAllPointsY(-1);                    
//					break;
//
//				default: 
//					break;
//				}
//				break;
//
//			default:
//				break;
//			}
//		}
//	}
//
//};
//
//
