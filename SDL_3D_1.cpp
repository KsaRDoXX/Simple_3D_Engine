#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "Vector3.h"
#include "Object3D.h"
#include "ObjectsController.h"

#undef main

int main(int argc, char* argv[])
{
    Window window(800, 600, "MainWindow");
    //Window menuWindow(500, 400, "optionsWindow");
    
   
    //objects
    std::vector<Object3D> allObjects;

     allObjects.emplace_back(Object3D({300,300,1500}, 70));
     
     allObjects[0].rotationX = 0.001;
     allObjects[0].rotationY = 0.0;
     allObjects[0].rotationZ = -0.0022;

     allObjects[0].speedX = 0.025;
     allObjects[0].speedY = -0.025;
     allObjects[0].speedZ = 0.0;
    

     allObjects.emplace_back(Object3D({-300,-300,1500},70));
   
     allObjects[1].speedX = -0.025;
     allObjects[1].speedY = 0.025;
     allObjects[1].speedZ = 0.0;
   
     allObjects[1].rotationX = 0.001;
     allObjects[1].rotationY = 0.00;
     allObjects[1].rotationZ = -0.0022;
   
     
     allObjects[0].mass = 5.002;
     allObjects[1].mass = 5.001;

     ObjectsController objController(allObjects);
  
     
    while (!window._closed)
    { 
        objController.RenderObjects(window.getRenderer());
        objController.PollObjectsEvents();
        objController.Gravitation();
        window.PollEvents();       
    }
    return 0;
}

