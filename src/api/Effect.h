#ifndef DANZUN_API_EFFECT_H_INCLUDED
#define DANZUN_API_EFFECT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../game/Effect.h"

namespace dan::api {
    class Effect {
        std::shared_ptr<::dan::Effect> effect;
    public:
        Effect(sol::this_state l, sol::function callback, sol::variadic_args args);
        ~Effect();

        void spawn(sol::table obj);
        void setRenderPriority(sol::this_state l, int value);
        void activate(sol::this_state l);
        void deactivate(sol::this_state l);

        static void open(sol::state_view lua);

    };
}

#endif
