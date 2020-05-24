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
        ThreeDimension::Vector translationVector = ThreeDimension::Vector(0.0f, 0.0f, 0.0f);

        int flaps = 0;
    public:
        Airplane(ThreeDimension::Vector startPosition, float startVelocity);

        ThreeDimension::Vector position = ThreeDimension::Vector(0.0f, 0.0f, 0.0f);
        float velocity = 0;
        float maxVelocity = 1.5;
        float minVelocity = 0.3;


        float tailVerticalAngle = 0.0;
        float maxTailVerticalAngle = 30.0;
        int idleTailVerticalAngleChange = 0;

        float tailHorizontalAngle = 0.0;
        float maxTailHorizontalAngle = 30.0;
        int idleTailHorizontalAngleChange = 0;

        float flapsAngle = 0.0;
        float maxFlapsAngle = 20.0;


        float aileronAngle = 0.0;
        float maxAileronAngle = 30.0;
        int idleAileronAngleChange = 0;

        float roll, yaw, pitch = 0;

        float getVelocity();

        void increaseVelocity();

        void decreaseVelocity();

        void increaseTailHorizontalAngle();

        void decreaseTailHorizontalAngle();

        void negateTailHorizontalAngle();

        void resetHorizontalAngleIdle();


        void increaseTailVerticalAngle();

        void decreaseTailVerticalAngle();

        void negateTailVerticalAngle();

        void resetVerticalAngleIdle();

        void increaseAileronAngle();

        void decreaseAileronAngle();

        void negateAileronAngle();

        void resetAileronIdle();

        void update();

    };
}


#endif //OPENGL_3DENGINE_AIRPLANE_H
