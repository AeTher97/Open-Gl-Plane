//
// Created by Mateusz on 31.03.2020.
//

#ifndef OPENGL_3DENGINE_AIRPLANE_H
#define OPENGL_3DENGINE_AIRPLANE_H

#include "Vector.h"

namespace airplane {

    class Airplane {
    private:
        ThreeDimension::Vector position = ThreeDimension::Vector();
        ThreeDimension::Vector translationVector = ThreeDimension::Vector();
        float velocity = 0;
        int flaps = 0;
    public:
        Airplane(ThreeDimension::Vector  startPosition, float startVelocity);
    };
}


#endif //OPENGL_3DENGINE_AIRPLANE_H
