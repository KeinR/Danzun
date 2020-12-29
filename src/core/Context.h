#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <atomic>

#include <sol/sol.hpp>

namespace dan {
    class Engine;
    class Shader;
}

namespace dan {
    class Context {
        // Is only for use by client code - The context has
        // no use for this
        Engine *engine;
        std::atomic<Shader*> currentShader;
        int vWidth;
        int vHeight;

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

        void lock();
        void unlock();

        static Context &fromLua(sol::state_view lua);
    };
}

#endif
