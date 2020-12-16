#include "Entity.h"

#include "../game/Entity.h"
#include "PatternVars.h"

dan::api::Entity::Entity(::dan::Entity &handle): handle(&handle) {
}
void dan::api::Entity::addVars(sol::userdata patternVars) {
    if (patternVars.is<PatternVars>()) {
        if (handle->addReference(patternVars)) {
            handle->regSymbolTable(patternVars.as<PatternVars>().getTable());
        }
    } else {
        throw std::runtime_error("Paramater not of type PatternVars");
    }
}

// Static members

void dan::api::Entity::open(sol::state_view &lua) {
    sol::usertype<Entity> type = lua.new_usertype<Entity>("Entity");

    type["addVars"] = &Entity::addVars;
}
