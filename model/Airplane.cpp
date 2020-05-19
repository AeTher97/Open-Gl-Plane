//
// Created by Mateusz on 31.03.2020.
//
#include <iostream>
#include "math.h"
#include "Airplane.h"

namespace airplane {

    Airplane::Airplane(ThreeDimension::Vector startPosition, float startVelocity) {
        this->position = startPosition;
        this->velocity = startVelocity;
    }

    float Airplane::getVelocity() {
        return this->velocity;
    }

    void Airplane::increaseVelocity() {
        if (velocity + velocityStep <= maxVelocity)
            velocity += velocityStep;

    }

    void Airplane::decreaseVelocity() {
        if (velocity - velocityStep > minVelocity)
            velocity -= velocityStep;

    }

    void Airplane::increaseAileronAngle() {
        resetAileronIdle();
        if (aileronAngle >= maxAileronAngle) {
            return;
        } else {
            aileronAngle += 1.0;
        }
    }

    void Airplane::decreaseAileronAngle() {
        resetAileronIdle();
        if (aileronAngle <= -maxAileronAngle) {
            return;
        } else {
            aileronAngle -= 1.0;
        }
    }

    void Airplane::negateAileronAngle() {
        if (aileronAngle == 0) {
            return;
        }
        if (aileronAngle > 0) {
            aileronAngle -= 1.0;
        } else {
            aileronAngle += 1.0;
        }
    }

    void Airplane::resetAileronIdle() {
        idleAileronAngleChange = 0;
    }


    void Airplane::increaseTailVerticalAngle() {
        resetVerticalAngleIdle();
        if (tailVerticalAngle >= maxTailVerticalAngle) {
            return;
        } else {
            tailVerticalAngle += 1.0;
        }
    }

    void Airplane::decreaseTailVerticalAngle() {
        resetVerticalAngleIdle();
        if (tailVerticalAngle <= -maxTailVerticalAngle) {
            return;
        } else {
            tailVerticalAngle -= 1.0;
        }
    }

    void Airplane::negateTailVerticalAngle() {
        if (tailVerticalAngle == 0) {
            return;
        }
        if (tailVerticalAngle > 0) {
            tailVerticalAngle -= 1.0;
        } else {
            tailVerticalAngle += 1.0;
        }
    }

    void Airplane::resetVerticalAngleIdle() {
        idleTailVerticalAngleChange = 0;
    }

    void Airplane::increaseTailHorizontalAngle() {
        resetHorizontalAngleIdle();
        if (tailHorizontalAngle >= maxTailHorizontalAngle) {
            return;
        } else {
            tailHorizontalAngle += 1.0;
        }
    }

    void Airplane::decreaseTailHorizontalAngle() {
        resetHorizontalAngleIdle();
        if (tailHorizontalAngle <= -maxTailHorizontalAngle) {
            return;
        } else {
            tailHorizontalAngle -= 1.0;
        }
    }

    void Airplane::negateTailHorizontalAngle() {
        if (tailHorizontalAngle == 0) {
            return;
        }
        if (tailHorizontalAngle > 0) {
            tailHorizontalAngle -= 1.0;
        } else {
            tailHorizontalAngle += 1.0;
        }

    }

    void Airplane::resetHorizontalAngleIdle() {
        idleTailHorizontalAngleChange = 0;
    }


    void Airplane::update() {
        yaw -= tailVerticalAngle / 20 * cos((double) roll / 360 * 6.28);
        pitch += tailVerticalAngle / 20 * sin((double) roll / 360 * 6.28);
        pitch -= tailHorizontalAngle / 20 * cos((double) roll / 360 * 6.28);
        yaw -= tailHorizontalAngle / 20 * sin((double) roll / 360 * 6.28);

        roll -= aileronAngle / 20;
        if (roll < -360) {
            roll += 360;
        }
        if (roll > 360) {
            roll -= 360;
        }

        if (idleTailHorizontalAngleChange > 20) {
            negateTailHorizontalAngle();
        }

        if (idleTailVerticalAngleChange > 20) {
            negateTailVerticalAngle();
        }

        if (idleAileronAngleChange > 20) {
            negateAileronAngle();
        }

        flapsAngle = (maxVelocity - velocity) / (maxVelocity - minVelocity) * maxFlapsAngle;


        idleTailVerticalAngleChange++;
        idleTailHorizontalAngleChange++;
        idleAileronAngleChange++;

    }

}
