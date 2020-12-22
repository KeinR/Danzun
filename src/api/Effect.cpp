#include "Effect.h"

#include <iostream>

#include "../game/Entity.h"
#include "../game/Game.h"

dan::api::Effect::Effect(sol::this_state l, sol::table masterObject, sol::function callback):
    masterObject(masterObject), callback(callback), lua(l) {
}
void dan::api::Effect::spawn(sol::table obj) {
    objects.push_back(obj);
}
void dan::api::Effect::render(Context &c) {
    sol::table params = lua.create_table();
    for (objects_t::iterator it = objects.begin(); it < objects.end();) {
        auto p = (*it)["done"];
        bool done;
        switch (p.get_type()) {
            case sol::type::boolean:
                done = p.get<bool>();
                break;
            case sol::type::number:
                done = static_cast<bool>(p.get<float>());
                break;
            default:
                done = false;
        }
        if (done) {
            it = objects.erase(it);
        } else {
            params.add(*it);
            ++it;
        }
    }
    sol::function_result result = callback.call(masterObject, params);
    if (!result.valid()) {
        // TEMP
        sol::error e = result;
        std::cerr << "Effect: CALLBACK ERROR'd: " << e.what() << '\n';
    }
}

// Static members

std::shared_ptr<dan::api::Effect> dan::api::Effect::make(sol::this_state l,
    sol::table masterObject, sol::function callback, int renderPriority)
{
    std::shared_ptr<Effect> ptr = std::make_shared<Effect>(l, masterObject, callback);
    Game::fromLua(l).submitRenderable(renderPriority, ptr);
    return ptr;
}

void dan::api::Effect::open(sol::state_view lua) {
    sol::usertype<Effect> type = lua.new_usertype<Effect>("Effect");

    type[sol::meta_function::construct] = &Effect::make;

    type["spawn"] = &Effect::spawn;
}
