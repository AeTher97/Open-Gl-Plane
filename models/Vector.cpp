//
// Created by Mateusz on 31.03.2020.
//

#include "Vector.h"

namespace ThreeDimension {

    void Vector::changeVector(float x, float y, float z) {
        this->x +=x;
        this->y +=y;
        this->z +=z;
    }

    float Vector::getXValue() {
        return x;
    }

    float Vector::getYValue() {
        return y;
    }

    float Vector::getZValue() {
        return z;
    }
}
