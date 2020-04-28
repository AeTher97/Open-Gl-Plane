//
// Created by Mateusz on 31.03.2020.
//

#ifndef OPENGL_3DENGINE_VECTOR_H
#define OPENGL_3DENGINE_VECTOR_H

namespace ThreeDimension {


    class Vector {
    private:

    public:
        float x, y, z = 0.0f;
        void changeVector(float x, float y, float z);
        float getXValue();
        float getYValue();
        float getZValue();

        Vector(float x, float y, float z);

        Vector(Vector *pVector);
    };
}


#endif //OPENGL_3DENGINE_VECTOR_H
