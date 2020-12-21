#include "Effect.h"

#include <iostream>

dan::Effect::Effect(sol::state_view lua, sol::table masterObject, sol::function callback):
    masterObject(masterObject), callback(callback), lua(lua) {
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
