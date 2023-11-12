#pragma once
#include "Object3D.h"
#include <vector>

class ObjectsController
{

private :
	std::vector<Object3D> objects3D = {};

public:	

	ObjectsController(std::vector<Object3D> obj);
	ObjectsController();
	~ObjectsController();
	
	void RenderObjects(SDL_Renderer* renderer);
	void Collision();
	void Gravitation();
	void PollObjectsEvents();

};

