//
// Created by micha on 04.03.2020.
//

#ifndef OPENGL_3DENGINE_WINDOW_H
#define OPENGL_3DENGINE_WINDOW_H


#include <GL/glut.h>
#include <cmath>
#include "Camera.h"
#include "Collisions.h"

class Window {

    Collisions collisions;


public:
    Camera camera;


    Window(Collisions &collisions) {
        this->collisions = collisions;
    }


};


#endif //OPENGL_3DENGINE_WINDOW_H
