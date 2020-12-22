#ifndef DAN_API_EFFECT_H_INCLUDED
#define DAN_API_EFFECT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

namespace dan {
    class Game;
    class Effect;
}

namespace dan::api {
    class Effect {
    public:
        typedef std::shared_ptr<::dan::Effect> handle_t;
    private:
        handle_t handle;
    public:
        Effect(sol::this_state l, sol::table masterObject, sol::function callback, int renderPriority);

        void spawn(sol::table object);

        static void open(sol::state_view &lua);
    };
}

#endif
