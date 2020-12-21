#ifndef DAN_API_EFFECT_H_INCLUDED
#define DAN_API_EFFECT_H_INCLUDED

#include <sol/sol.hpp>

namespace dan {
    class Game;
    class Effect;
}

namespace dan::api {
    class Effect {
        ::dan::Effect *handle;
        Game *game;
    public:
        Effect(sol::this_state l, sol::table masterObject, sol::function callback, int renderPriority);
        ~Effect();

        void spawn(sol::table object);

        static void open(sol::state_view &lua);
    };
}

#endif
