#include "Entity.h"

#include <vector>

#include "../game/Entity.h"
#include "PatternVars.h"

dan::api::Entity::Entity(const handle_t &handle): handle(handle) {
}

dan::api::Entity::handle_t dan::api::Entity::getHandle() {
    return handle;
}

void dan::api::Entity::setScript(sol::this_state l, sol::function func, sol::variadic_args pargs) {
    handle->setScript(handle, l, func, std::vector<sol::object>(pargs.begin(), pargs.end()));
}

int dan::api::Entity::getX() {
    return handle->getX();
}
int dan::api::Entity::getY() {
    return handle->getY();
}

// Static members

void dan::api::Entity::open(sol::state_view &lua) {
    sol::usertype<Entity> type = lua.new_usertype<Entity>("Entity");

    type["setScript"] = &Entity::setScript;
    type["getX"] = &Entity::getX;
    type["getY"] = &Entity::getY;
}
