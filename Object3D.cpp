#include <iostream>
#include "Object3D.h"

Vector2 Object3D:: PerspectiveProjection(Vector3 v)
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

	o._x = (v._x * matProj.m[0][0] + v._y * matProj.m[1][0] + v._z * matProj.m[2][0] + matProj.m[3][0]);
	o._y = (v._x * matProj.m[0][1] + v._y * matProj.m[1][1] + v._z * matProj.m[2][1] + matProj.m[3][1]);
	o._z = (v._x * matProj.m[0][2] + v._y * matProj.m[1][2] + v._z * matProj.m[2][2] + matProj.m[3][2]);
	float w = v._x*matProj.m[0][3] + v._y * matProj.m[1][3] + v._z * matProj.m[2][3] + matProj.m[3][3];

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

//weak perspective projection
Vector2 Object3D::weakProjection(Vector3 v)
{

	double focalLenght = 10.0;
	Vector2 v2(0, 0);

	
	//       400 = windowWidth / 2 
	v2._x = (400 + (focalLenght * v._x / (focalLenght + v._z) * scale));
	v2._y = (300 + (focalLenght * v._y) / (focalLenght + v._z) * scale);
	return v2;
}


void Object3D::RotateAllPointsX(double rotation)
{
	for (int i = 0; i < modelSpacePoints3D.size(); i++)
	{
		modelSpacePoints3D[i].RotateX(rotation);
	}
}

void Object3D::RotateAllPointsY(double rotation)
{
	for (int i = 0; i < modelSpacePoints3D.size(); i++)
	{
		modelSpacePoints3D[i].RotateY(rotation);
	}
}

void Object3D::RotateAllPointsZ(double rotation)
{
	for (int i = 0; i < modelSpacePoints3D.size(); i++)
	{
		modelSpacePoints3D[i].RotateZ(rotation);
	}
}

void Object3D::TranslateAllWorldPoints()
{
	for (int i = 0; i < worldSpacePoints3D.size(); i++)
	{
		worldSpacePoints3D[i].TranslateX(translationX);
		worldSpacePoints3D[i].TranslateY(translationY);
		worldSpacePoints3D[i].TranslateZ(translationZ);
	}
}

std::vector<Vector3> modelSpacePoints3D;
std::vector<Vector3> worldSpacePoints3D;

std::vector<Vector2> points2D;
std::vector<Vertices> vertices;

Object3D::Object3D(Vector3 startPos, double scale) :
	scale(scale)
{ 
	modelSpacePoints3D = {
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

	worldSpacePoints3D = modelSpacePoints3D;

	//uses translationXYZ to translate world points
	TranslateAllWorldPoints();
}


Vector3 Object3D::ScaleVector(Vector3 v, double scale)
{
	Vector3 scaledVector(v._x * scale, v._y * scale, v._z * scale);
	return scaledVector;
}

Vector3 Object3D::averagePoint(std::vector<Vector3> vectors)
{
	Vector3 v3(0, 0, 0);
	for (int i = 0; i < vectors.size(); i++)
	{
		v3._x += vectors[i]._x;
		v3._y += vectors[i]._y;
		v3._z += vectors[i]._z;
	}

	v3._x /= (vectors.size() + 1);
	v3._y /= (vectors.size() + 1);
	v3._z /= (vectors.size() + 1);

	return v3;
}

void Object3D::Render(SDL_Renderer* renderer)
{
	for (Vertices ver : vertices)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration(0);

		//rotating - modelspace 

		modelSpacePoints3D[ver._start].RotateX(rotationX);
		modelSpacePoints3D[ver._start].RotateY(rotationY);
		modelSpacePoints3D[ver._start].RotateZ(rotationZ);

		modelSpacePoints3D[ver._end].RotateX(rotationX);
		modelSpacePoints3D[ver._end].RotateY(rotationY);
		modelSpacePoints3D[ver._end].RotateZ(rotationZ);

		//update world space points 
		worldSpacePoints3D[ver._start]._x = modelSpacePoints3D[ver._start]._x + translationX;
		worldSpacePoints3D[ver._start]._y = modelSpacePoints3D[ver._start]._y + translationY;
		worldSpacePoints3D[ver._start]._z = modelSpacePoints3D[ver._start]._z + translationZ;

		worldSpacePoints3D[ver._end]._x = modelSpacePoints3D[ver._end]._x + translationX;
		worldSpacePoints3D[ver._end]._y = modelSpacePoints3D[ver._end]._y + translationY;
		worldSpacePoints3D[ver._end]._z = modelSpacePoints3D[ver._end]._z + translationZ;

		  // Physics 
		// speed
		translationX += speedX;
		translationY += speedY;
		translationZ += speedZ;

		//acceleration 
		speedX += accelerationX;
		speedY += accelerationY;
		speedZ += accelerationZ;

		massCenter = averagePoint(worldSpacePoints3D);
		Vector2 massCenter2D = weakProjection(massCenter);

		 //displaying

		startPoint3D = worldSpacePoints3D[ver._start];
		endPoint3D = worldSpacePoints3D[ver._end];

		Vector2 startPoint2D = weakProjection(startPoint3D); Vector2 endPoint2D = weakProjection(endPoint3D);
		//Vector2 startPoint2D = PerspectiveProjection(startPoint3D); Vector2 endPoint2D = PerspectiveProjection(endPoint3D);	

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 125);
		SDL_RenderDrawPoint(renderer, massCenter2D._x, massCenter2D._y);
		SDL_RenderDrawLine(renderer, startPoint2D._x, startPoint2D._y, endPoint2D._x, endPoint2D._y);

		//time 
		auto time2 = std::chrono::high_resolution_clock::now();
		duration = time2 - time1;
		DeltaTime = duration.count();
		time1 = time2;

	}
}



void Object3D::TranslateXYZ(double x, double y, double z)
{
	for (int i = 0; i < modelSpacePoints3D.size(); i++)
	{
		translationX += x;
		translationY += y;
		translationZ += z;
	}
}