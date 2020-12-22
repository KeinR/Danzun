#ifndef DAN_API_EFFECT_H_INCLUDED
#define DAN_API_EFFECT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "../sprite/Renderable.h"

namespace dan::api {
    class Effect: public Renderable {
        typedef std::vector<sol::table> objects_t;
        sol::table masterObject;
        objects_t objects;
        sol::function callback;
        sol::state_view lua;
    public:
        Effect(sol::this_state l, sol::table masterObject, sol::function callback);
        void spawn(sol::table obj);
        void render(Context &c) override;

        static std::shared_ptr<Effect> make(sol::this_state l,
            sol::table masterObject, sol::function callback, int renderPriority);

        static void open(sol::state_view lua);
    };
}

#endif
