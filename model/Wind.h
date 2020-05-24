//
// Created by Mateusz on 24.05.2020.
//

#ifndef OPENGL_3DENGINE_WIND_H
#define OPENGL_3DENGINE_WIND_H


#include "Vector.h"

class Wind {
    private:
    ThreeDimension::Vector windVector = ThreeDimension::Vector(0, 0, 0);
        float windVelocity;
    public:
        Wind(ThreeDimension::Vector windVector, float windVelocity);
        float getXWindMove();
        float getZWindMove();

};


#endif //OPENGL_3DENGINE_WIND_H
