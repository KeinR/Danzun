#ifndef DANZUN_MATRIX_H_INCLUDED
#define DANZUN_MATRIX_H_INCLUDED

namespace dan {
    class Engine;
}

namespace dan {
    class Matrix {
    public:
        // [In screen coords]

        // Translation
        float x;
        float y;
        float z;
        // Scaling
        float width;
        float height;

        // Rotation
        // [In degrees]
        float rotation;

        bool reflectAcrossYAxis;

        Matrix(float x = 0.0f, float y = 0.0f, float z = 0.0f, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, bool reflectAcrossYAxis = false);
        void load(const RenderContext &info);
    };
};

#endif
