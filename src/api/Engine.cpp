#include "Engine.h"

#include <sol/sol.hpp>

#include "../core/Engine.h"

dan::api::Engine::Engine(::dan::Engine &handle): handle(&handle) {
}

void dan::api::Engine::term(int status) {
    // A REALLY BAD temporary solution
    exit(status);
}

::dan::Engine *dan::api::Engine::getHandle() {
    // For internal use only
    return handle;
}

void dan::api::Engine::open(sol::state_view &lua) {
    sol::usertype<Engine> type = lua.new_usertype<Engine>("Engine");

    type["exit"] = &Engine::term;
    type["getHandle"] = &Engine::getHandle;

}
