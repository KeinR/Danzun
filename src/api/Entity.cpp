#include "Entity.h"

#include <vector>

#include "../game/Game.h"
#include "../game/Entity.h"
#include "PatternVars.h"
#include "../core/debug.h"
#include "Script.h"

dan::api::Entity::Entity(const handle_t &v): handle(v) {
}

dan::api::Entity::Entity(
    sol::this_state l,
    sol::function hitCallback, const std::shared_ptr<RenderConfig> &disp,
    const std::string &equation, sol::variadic_args vars
) {

    Game &g = ::dan::Game::fromLua(l);

    std::vector<PatternVars::symTable_t> tables;
    tables.reserve(vars.size()+1);
    for (auto d : vars) {
        if (d.is<PatternVars>()) {
            tables.push_back(d.as<PatternVars>().getTable());
        }
    }
    // Lowest priority
    tables.push_back(g.getGlobalSymbols());

    handle = std::make_shared<::dan::Entity>(
        g,
        hitCallback,
        disp,
        equation,
        tables
    );
    g.addEntity(handle);

    activate(l);
}

dan::api::Entity::handle_t dan::api::Entity::getHandle() {
    return handle;
}

void dan::api::Entity::setScript(const Script &s) {
    handle->setScript(s);
}

void dan::api::Entity::activate(sol::this_state l) {
    Game::fromLua(l).submitRenderable(handle->getRenderPriority(), handle);
}
void dan::api::Entity::deactivate(sol::this_state l) {
    Game::fromLua(l).removeRenderable(handle.get());
}
void dan::api::Entity::setRenderPriority(sol::this_state l, int value) {
    deactivate(l);
    handle->setRenderPriority(value);
    activate(l);
}

void dan::api::Entity::regCircle(sol::this_state l, const std::string &group) {
    handle->getGroups().insert(group);
    Game::fromLua(l).getGroup(group).pushCircle(handle);
}
void dan::api::Entity::regPolygon(sol::this_state l, const std::string &group, sol::table points) {
    DANZUN_ASSERT(false); // NOT IMPLEMENTED

    // groups.insert(group);
    // Game::fromLua(l).getGroup(group).pushPolygon(handle);
}
void dan::api::Entity::unregHitboxes(sol::this_state l) {
    Game &g = Game::fromLua(l);
    for (const std::string &name : handle->getGroups()) {
        g.getGroup(name).erase(handle.get());
    }
    handle->getGroups().clear();
}

float dan::api::Entity::index(const std::string &name) {
    auto *v = handle->getTable().get_variable(name);
    return v == nullptr ? 0 : v->value();
}
void dan::api::Entity::newIndex(const std::string &name, float value) {
    auto *v = handle->getTable().get_variable(name);
    if (v != nullptr) {
        v->ref() = value;
    }
}
void dan::api::Entity::newIndexBool(const std::string &name, bool value) {
    newIndex(name, static_cast<float>(value));
}

// Static members

void dan::api::Entity::open(sol::state_view &lua) {
    sol::usertype<Entity> type = lua.new_usertype<Entity>("Entity",
        sol::constructors<Entity(sol::this_state,
            sol::function,const std::shared_ptr<RenderConfig>&,
            const std::string&,sol::variadic_args)>()
    );

    type[sol::meta_function::index] = &Entity::index;
    type[sol::meta_function::new_index] = sol::overload(&Entity::newIndex, &Entity::newIndexBool);

    type["setScript"] = &Entity::setScript;
    type["activate"] = &Entity::activate;
    type["deactivate"] = &Entity::deactivate;
    type["setRenderPriority"] = &Entity::setRenderPriority;
    type["regCircle"] = &Entity::regCircle;
    type["regPolygon"] = &Entity::regPolygon;
    type["unregHitboxes"] = &Entity::unregHitboxes;

}
