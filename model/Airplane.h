//
// Created by Mateusz on 31.03.2020.
//

#ifndef OPENGL_3DENGINE_AIRPLANE_H
#define OPENGL_3DENGINE_AIRPLANE_H

#include "Vector.h"

namespace airplane {

    class Airplane {
    private:
        const float velocityStep = 0.1;
        ThreeDimension::Vector translationVector = ThreeDimension::Vector(0.0f,0.0f,0.0f);
        float velocity = 0;
        int flaps = 0;
    public:
        Airplane(ThreeDimension::Vector startPosition, float startVelocity);
        ThreeDimension::Vector position = ThreeDimension::Vector(0.0f,0.0f,0.0f);
        int xRotate, yRotate, zRotate = 0;
        ThreeDimension::Vector getPosition();
        void changePosition();
        float getVelocity();
        void increaseVelocity();
        void decreaseVelocity();
    };
}


#endif //OPENGL_3DENGINE_AIRPLANE_H
