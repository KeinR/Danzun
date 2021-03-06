#include "Effect.h"

#include "../game/Game.h"
#include "../core/error.h"
#include "../core/Context.h"
#include "../core/Engine.h"

dan::Effect::Effect(int priority, args_t args, sol::function callback):
    args(args), callback(callback), renderPriority(priority), detached(false) {
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

void dan::Effect::spawn(sol::object obj) {
    objects.push_back(obj);
}
void dan::Effect::render(Context &c) {
    if (objects.empty()) {
        return;
    }

    sol::state_view lua = c.getEngine().getState();
    // Package parameters into single table
    sol::table params = lua.create_table();
    for (objects_t::iterator it = objects.begin(); it < objects.end();) {
        // If the prop "done" is set to true, then delete
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
    // Important that we forward the user parameters first for safety
    sol::function_result result = callback.call(sol::as_args(args), params);
    if (!result.valid()) {
        sol::error e = result;
        err("Effect::render") << "Effect callback failed: " << e.what() << '\n';
    }
}
