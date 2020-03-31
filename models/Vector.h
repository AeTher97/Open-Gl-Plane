//
// Created by Mateusz on 31.03.2020.
//

#ifndef OPENGL_3DENGINE_VECTOR_H
#define OPENGL_3DENGINE_VECTOR_H

namespace ThreeDimension {


    class Vector {
    private:
        float x, y, z = 0.0f;
    public:
        void changeVector(float x, float y, float z);
        float getXValue();
        float getYValue();
        float getZValue();
    };
}


#endif //OPENGL_3DENGINE_VECTOR_H
