#include "Effect.h"

#include <vector>

#include "../game/Game.h"

dan::api::Effect::Effect(sol::this_state l, sol::function callback, sol::variadic_args args):
    effect(std::make_shared<::dan::Effect>(l, std::vector<sol::object>(args.begin(), args.end()), callback)),
    activated(false)
{
    activate(l);
}
dan::api::Effect::~Effect() {
    effect->setDetached(true);
}

void dan::api::Effect::spawn(sol::table obj) {
    effect->spawn(obj);
}

void dan::api::Effect::setRenderPriority(sol::this_state l, int value) {
    deactivate(l);
    effect->setRenderPriority(value);
    activate(l);
}
void dan::api::Effect::activate(sol::this_state l) {
    if (!activated) {
        activated = true;
        Game::fromLua(l).submitRenderable(effect->getRenderPriority(), effect);
    }
}
void dan::api::Effect::deactivate(sol::this_state l) {
    if (activated) {
        activated = false;
        Game::fromLua(l).removeRenderable(effect.get());
    }
}

// Static members

void dan::api::Effect::open(sol::state_view lua) {
    sol::usertype<Effect> type = lua.new_usertype<Effect>("Effect",
        sol::constructors<Effect(sol::this_state,sol::function,sol::variadic_args)>()
    );

    type["spawn"] = &Effect::spawn;
    type["setRenderPriority"] = &Effect::setRenderPriority;
    type["activate"] = &Effect::activate;
    type["deactivate"] = &Effect::deactivate;
}
