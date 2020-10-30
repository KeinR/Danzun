#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <string>
#include <memory>

#include "../gfs/Mesh.h"

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
        Engine *engine;
        shader_t currentShader;
        int fWidth;
        int fHeight;

    public:
        Context(Engine &e);

        void setShader(const shader_t &s);
        // Sets shader to nullptr
        void clearShader();

        void setFWidth(int w);
        void setFHeight(int h);

        int getFWidth() const;
        int getFHeight() const;
        const shader_t &getShader() const;
        Engine &getEngine() const;

        void renderQuad() const;
    };
}

#endif
