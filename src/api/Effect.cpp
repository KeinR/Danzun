#include "Effect.h"

#include "../game/Game.h"
#include "../game/Effect.h"

dan::api::Effect::Effect(sol::this_state l, sol::table masterObject, sol::function callback, int renderPriority) {
    handle = std::make_shared<::dan::Effect>(l, masterObject, callback);
    Game::fromLua(l).addEffect(handle, renderPriority);
}

void dan::api::Effect::spawn(sol::table object) {
    handle->spawn(object);
}

void dan::api::Effect::open(sol::state_view &lua) {
    sol::usertype<Effect> type = lua.new_usertype<Effect>("Effect",
        sol::constructors<Effect(sol::this_state,sol::table,sol::function,int)>()
    );

    type["spawn"] = &Effect::spawn;
}
