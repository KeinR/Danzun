#ifndef DANZUN_MATRIX_H_INCLUDED
#define DANZUN_MATRIX_H_INCLUDED

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
        Matrix(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, bool reflectAcrossYAxis = false);

        void load(Context &c);
    };
};

#endif
