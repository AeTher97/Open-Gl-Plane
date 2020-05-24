//
// Created by Mateusz on 24.05.2020.
//

#include "Wind.h"
#include "Vector.h"



float Wind::getXWindMove() {
    return windVector.x * windVelocity;
}


float Wind::getZWindMove() {
    return windVector.z * windVelocity;
}

Wind::Wind(ThreeDimension::Vector windVector, float windVelocity) {
    this -> windVector =  windVector;
    this -> windVelocity = windVelocity;
}

