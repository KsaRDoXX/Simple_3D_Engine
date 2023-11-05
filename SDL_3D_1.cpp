#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "Vector3.h"
#include "Object3D.h"
#include "Cube.h"
#include "ObjectsController.h"

#undef main


int main(int argc, char* argv[])
{
    Window window(800, 600, "MainWindow");
   
    std::vector<Object3D> allObjects;
    
    allObjects.emplace_back(Object3D({0,0,1000},50));
    allObjects[0].rotationX = 0.0003;
    allObjects[0].rotationY = 0.0001;
    allObjects[0].rotationZ = 0.0002;

    allObjects.emplace_back(Object3D({0,0,1000},30));
    allObjects[1].rotationX = 0.0003;
    allObjects[1].rotationY = 0.0001;
    allObjects[1].rotationZ = 0.0002;
   
    ObjectsController objController(allObjects);
  
    while (!window._closed)
    { 
        objController.RenderObjects(window.getRenderer());
        objController.PollObjectsEvents();
        window.PollEvents();
    }
    return 0;
}

