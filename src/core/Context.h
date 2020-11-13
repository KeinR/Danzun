#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <string>
#include <memory>

#include "../gfs/Mesh.h"
#include "../Clock.h"

namespace dan {
    class Engine;
    class Shader;
}

namespace dan {
    class Context {
    public:
        typedef std::shared_ptr<Shader> shader_t;
    private:
        Mesh quad_;
        // Is only for use by client code - The engine has
        // no use for this
        Engine *engine;
        shader_t currentShader;
        int vWidth;
        int vHeight;

        Clock clock;

    public:
        Context(Engine *e);

        void setShader(const shader_t &s);
        // Sets shader to nullptr
        void clearShader();

        void setViewport(int w, int h);

        int getVPWidth() const;
        int getVPHeight() const;
        const shader_t &getShader() const;
        Engine &getEngine() const;

        Clock &getClock();

        void renderQuad() const;
    };
}

#endif
