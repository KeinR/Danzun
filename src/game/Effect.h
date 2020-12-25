#ifndef DAN_EFFECT_H_INCLUDED
#define DAN_EFFECT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "Renderable.h"

namespace dan {
    class Effect: public Renderable {
        typedef std::vector<sol::table> objects_t;
        sol::object masterObject;
        objects_t objects;
        sol::function callback;
        sol::state_view lua;
        int renderPriority;
        bool detached;
    public:
        Effect(sol::state_view l, sol::object masterObject, sol::function callback);

        void setDetached(bool value);

        void setRenderPriority(int value);
        int getRenderPriority();

        void spawn(sol::table obj);

        void render(Context &c) override;
    };
}

#endif
