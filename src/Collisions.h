//
// Created by micha on 04.03.2020.
//

#define MIN_DISTANCE 0.5            // minimalny dystans od brzegu obszaru ograniczenia kamery

#ifndef OPENGL_3DENGINE_COLLISIONS_H
#define OPENGL_3DENGINE_COLLISIONS_H

#include <cstdio>
#include "Camera.h"

struct obstacle {
    obstacle *next;
    double posX1;
    double posZ1;
    double posX2;
    double posZ2;
};

class Collisions {

    obstacle *obstacleArea = NULL;

public:

    bool isIntersecting(double posX, double posZ, Camera camera) {
        if (posX * posX + posZ * posZ > (camera.area - MIN_DISTANCE * 2) * (camera.area - MIN_DISTANCE * 2))
            return false;
        obstacle *pom = obstacleArea;
        while (pom) {
            if (pom->posX1 < posX &&
                pom->posX2 > posX &&
                pom->posZ1 < posZ &&
                pom->posZ2 > posZ)
                return false;
            pom = pom->next;
        }
        return true;
    }

    void registerObstacle(double X1, double Z1, double X2, double Z2) {
        obstacle *pom = new obstacle;
        if (X1 > X2) {
            double tmp = X1;
            X1 = X2;
            X2 = tmp;
        }
        if (Z1 > Z2) {
            double tmp = Z1;
            Z1 = Z2;
            Z2 = tmp;
        }
        pom->posX1 = X1;
        pom->posZ1 = Z1;
        pom->posX2 = X2;
        pom->posZ2 = Z2;
        pom->next = obstacleArea;
        obstacleArea = pom;
    }
};

#endif //OPENGL_3DENGINE_COLLISIONS_H
