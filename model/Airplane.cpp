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
}
