#ifndef DANZUN_MATRIX_H_INCLUDED
#define DANZUN_MATRIX_H_INCLUDED

#include <string>

#include <glm/glm.hpp>

namespace dan {
    class Context;
}

namespace dan {
    /// @TODO: Getters and setters
    class Matrix {
    public:
        // [In screen coords]

        // Translation
        float x;
        float y;
        // Pivot relative to x/y (in NDC)
        float pivotXOfs;
        float pivotYOfs;
        // Scaling
        float width;
        float height;

        // Rotation
        // [In radians]
        float rotation;

        bool reflectAcrossYAxis;

        Matrix(float x, float y, float pivotXOfs, float pivotYOfs, float width, float height, float rotation, bool reflectAcrossYAxis);

        glm::mat4 getModel(bool flipY);
        glm::mat4 getData(Context &c);

        void load(Context &c, const std::string &location = "model");
    };
}

#endif
