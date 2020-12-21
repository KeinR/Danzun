#ifndef DAN_EFFECT_H_INCLUDED
#define DAN_EFFECT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "../sprite/Renderable.h"

namespace dan {
    class Effect: public Renderable {
        typedef std::vector<sol::table> objects_t;
        sol::table masterObject;
        objects_t objects;
        sol::function callback;
        sol::state_view lua;
    public:
        Effect(sol::state_view lua, sol::table masterObject, sol::function callback);
        void spawn(sol::table obj);
        void render(Context &c) override;
    };
}

#endif
