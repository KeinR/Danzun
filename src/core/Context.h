#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <string>

#include "../gfs/Mesh.h"

namespace dan {
    class Engine;
    class Shader;
}

namespace dan {
    class Context {
        Mesh quad_;
        Engine *engine;
        Shader *currentShader;
        int fWidth;
        int fHeight;

    public:
        Context(Engine &e);

        void setShader(Shader &s);
        // Sets shader to nullptr
        void clearShader();

        void setFWidth(int w);
        void setFHeight(int h);

        int getFWidth() const;
        int getFHeight() const;
        Shader &getShader() const;
        Engine &getEngine() const;

        void renderQuad() const;
    };
}

#endif
