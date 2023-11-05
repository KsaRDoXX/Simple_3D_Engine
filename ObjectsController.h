#pragma once
#include "Object3D.h"
#include <vector>

class ObjectsController
{

private :
	std::vector<Object3D> objects3D = {};
public: 
	ObjectsController(std::vector<Object3D> obj) :
		objects3D(obj)
	{
		std::cout << "WASD -> kontroluje obracanie \n strzalki -> przesuwanie osie XY \n cyfra '0' i '1' -> przesuwanie os Z\n";
	}

	ObjectsController()
	{
		
	}

	~ObjectsController()
	{

	}

	void RenderObjects(SDL_Renderer* renderer)
	{
		for (int i = 0; i < objects3D.size(); i++)
		{
			objects3D[i].Render(renderer);
		}

		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
	}

	void PollObjectsEvents()
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
							objects3D[i].TranslateXYZ(0, 0, -1 );
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
		
		
	

	
};

