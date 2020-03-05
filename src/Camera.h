//
// Created by micha on 04.03.2020.
//

#ifndef OPENGL_3DENGINE_CAMERA_H
#define OPENGL_3DENGINE_CAMERA_H


class Camera {

public:
    double x;
    double y;
    double z;
    double pointy;
    double yPointSpeed;
    double speed;
    double translation;
    double angle;
    double rotationSpeed;
    double area;
    bool isMoving;

    Camera() {
        x = 0;
        y = 0;
        z = 0;
        resetVariables();
    }

private:
    void resetVariables() {
        pointy = 0;
        yPointSpeed = 0;
        speed = 0;
        translation = 0;
        angle = 0;
        rotationSpeed = 0;
        area = 0;
        isMoving = false;
    }

    Camera(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        resetVariables();
    }

};


#endif //OPENGL_3DENGINE_CAMERA_H
