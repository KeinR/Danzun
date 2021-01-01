#ifndef DANZUN_EFFECT_H_INCLUDED
#define DANZUN_EFFECT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "Renderable.h"

namespace dan {
    class Effect: public Renderable {
        typedef std::vector<sol::table> objects_t;
		typedef std::vector<sol::object> args_t;
        args_t args;
		objects_t objects;
        sol::function callback;
        sol::state_view lua;
        int renderPriority;
        bool detached;
    public:
        Effect(sol::state_view lua, args_t args, sol::function callback);

        void setDetached(bool value);

        void setRenderPriority(int value);
        int getRenderPriority();

        void spawn(sol::object obj);

        void render(Context &c) override;
    };
}

#endif
