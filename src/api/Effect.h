#ifndef DAN_API_EFFECT_H_INCLUDED
#define DAN_API_EFFECT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../game/Effect.h"

namespace dan::api {
    class Effect {
        std::shared_ptr<::dan::Effect> effect;
    public:
        Effect(sol::this_state l, int renderPriority, sol::function callback, sol::object masterObject);
        ~Effect();

        void spawn(sol::table obj);
        void setRenderPriority(sol::this_state l, int value);
        void activate(sol::this_state l);
        void deactivate(sol::this_state l);

        static void open(sol::state_view lua);

    };
}

#endif
