#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <string>

#include "../render/Mesh.h"
#include "../time/Clock.h"

namespace dan {
    class Engine;
    class Shader;
}

namespace dan {
    class Context {
        Mesh quad_;
        // Is only for use by client code - The context has
        // no use for this
        Engine *engine;
        Shader *currentShader;
        int vWidth;
        int vHeight;

        Clock clock;

    public:
        Context(Engine *e);

        void setShader(Shader &s);
        // Sets shader to nullptr
        void clearShader();

        void setViewport(int w, int h);

        int getVPWidth() const;
        int getVPHeight() const;
        Shader &getShader() const;
        Engine &getEngine() const;
        Clock &getClock();

        void renderQuad() const;
    };
}

#endif
