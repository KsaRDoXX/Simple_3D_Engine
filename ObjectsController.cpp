#include "ObjectsController.h" 
#include <iostream>

ObjectsController::ObjectsController(std::vector<Object3D> obj) :
	objects3D(obj)
{
	std::cout << "WASD -> kontroluje obracanie \n strzalki -> przesuwanie osie XY \n cyfra '0' i '1' -> przesuwanie os Z\n";
}

ObjectsController::ObjectsController()
{
 
}

ObjectsController::~ObjectsController()
{
	
}

void ObjectsController::Gravitation()
{
	//F = G * (m1 * m2) / R^2
	double G = 0.008;

	for (int i = 0; i < objects3D.size(); i++)
	{
		for (int j = 0; j < objects3D.size(); j++)
		{
			//vectors between two centers of mass
			Vector3 gravityVector;

			if (objects3D[j].mass != objects3D[i].mass)
			{
				gravityVector._x = objects3D[j].massCenter._x - objects3D[i].massCenter._x;
				gravityVector._y = objects3D[j].massCenter._y - objects3D[i].massCenter._y;
				gravityVector._z = objects3D[j].massCenter._z - objects3D[i].massCenter._z;

				double distance;
				distance = sqrt((gravityVector._x) * (gravityVector._x) + (gravityVector._y) * (gravityVector._y) + (gravityVector._z) * (gravityVector._z));
				
		             		//radius
				if (distance > objects3D[j].a * 2)
				{
					double m = objects3D[i].mass * objects3D[j].mass;

					objects3D[i].accelerationX = (G * gravityVector._x * m) / (distance * distance);
					objects3D[i].accelerationY = (G * gravityVector._y * m) / (distance * distance);
					objects3D[i].accelerationZ = (G * gravityVector._z * m) / (distance * distance);
				}
				else
				{

					Collision();

				}
			}
		}
	}
}

void ObjectsController::Collision()
{
	std::cout << "collision occured";
	objects3D.pop_back();
}

void ObjectsController::PollObjectsEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case (SDL_KEYDOWN):

			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(-1, 0, 0);
				}

				break;

			case SDLK_RIGHT:

				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(1, 0, 0);
				}

				break;

			case SDLK_UP:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(0, -1, 0);
				}

				break;

			case SDLK_DOWN:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(0, 1, 0);
				}

				break;

			case SDLK_0:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(0, 0, 1);
				}

				break;

			case SDLK_1:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].TranslateXYZ(0, 0, -1);
				}

				break;

			case SDLK_w:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].rotationX -= .0001;
				}


				break;

			case SDLK_a:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].rotationY += .0001;
				}


				break;

			case SDLK_s:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].rotationX += .0001;
				}
				break;

			case SDLK_d:
				for (int i = 0; i < objects3D.size(); i++)
				{
					objects3D[i].rotationY -= .0001;
				}


				break;

			default:
				break;
			}
			break;



		default:
			break;
		}
	}
}

void ObjectsController::RenderObjects(SDL_Renderer* renderer)
{
	for (int i = 0; i < objects3D.size(); i++)
	{
		objects3D[i].Render(renderer);
	}

	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

}