//
// Created by Mateusz on 31.03.2020.
//

#include "Airplane.h"
namespace airplane{

    Airplane::Airplane(ThreeDimension::Vector startPosition, float startVelocity) {
        this->position = startPosition;
        this->velocity = startVelocity;
    }

    float Airplane::getVelocity() {
        return this->velocity;
    }

    void Airplane::increaseVelocity() {
        if(velocity + velocityStep <= 1)
            velocity += velocityStep;
    }

    void Airplane::decreaseVelocity() {
        if(velocity - velocityStep > 0)
            velocity -= velocityStep;
    }

    ThreeDimension::Vector Airplane::getPosition() {
        return position;
    }

    void Airplane::changePosition() {
        position.changeVector(0,0, velocity);
    }

    void Airplane::reset() {
        this->position = ThreeDimension::Vector(0.0f, 0.0f, 0.0f);
        this->velocity = 0.1;
        this->roll = 0;
        this->pitch = 0;
        this->yaw = 0;
    }

}
