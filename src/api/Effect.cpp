#include "Effect.h"

#include <iostream>

#include "../game/Game.h"

dan::api::Effect::Effect(sol::this_state l, int renderPriority, sol::function callback, sol::object masterObject):
    effect(std::make_shared<::dan::Effect>(l, masterObject, callback))
{
    effect->setRenderPriority(renderPriority);
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
    std::cout << "Activate effect" << '\n';
    Game::fromLua(l).submitRenderable(effect->getRenderPriority(), effect);
}
void dan::api::Effect::deactivate(sol::this_state l) {
    std::cout << "Deactivate effect" << '\n';
    Game::fromLua(l).removeRenderable(effect.get());
}

// Static members

void dan::api::Effect::open(sol::state_view lua) {
    sol::usertype<Effect> type = lua.new_usertype<Effect>("Effect",
        sol::constructors<Effect(sol::this_state,int,sol::function,sol::object)>()
    );

    type["spawn"] = &Effect::spawn;
    type["setRenderPriority"] = &Effect::setRenderPriority;
    type["activate"] = &Effect::activate;
    type["deactivate"] = &Effect::deactivate;
}
