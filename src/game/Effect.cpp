#include "Effect.h"

#include <iostream>

#include "../game/Entity.h"
#include "../game/Game.h"

dan::Effect::Effect(sol::state_view l, sol::object masterObject, sol::function callback):
    masterObject(masterObject), callback(callback), lua(l), renderPriority(0), detached(false) {
}

void dan::Effect::setDetached(bool value) {
    detached = value;
}

void dan::Effect::setRenderPriority(int value) {
    renderPriority = value;
}
int dan::Effect::getRenderPriority() {
    return renderPriority;
}

void dan::Effect::spawn(sol::table obj) {
    objects.push_back(obj);
}
void dan::Effect::render(Context &c) {
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

            // If detached is true, the Lua client object has been GC'd.
            // If there also are no objects left, there is no point
            // for this to exist anymore, as we do not expect that any
            // more objects can be added...
            // It is a given that it exists in the render queue.
            if (objects.empty() && detached) {
                Game::fromLua(lua).removeRenderable(this);
            }
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
