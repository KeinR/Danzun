#ifndef DANZUN_MATRIX_H_INCLUDED
#define DANZUN_MATRIX_H_INCLUDED

#include <string>

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
        // Scaling
        float width;
        float height;

        // Rotation
        // [In radians]
        float rotation;

        bool reflectAcrossYAxis;
        Matrix(float x, float y, float width, float height, float rotation, bool reflectAcrossYAxis);

        void load(Context &c, const std::string &location = "model");
    };
};

#endif
