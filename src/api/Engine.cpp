#include "engine.h"

#include <sol/sol.hpp>

dan::api::Engine::Engine(::dan::Engine &handle): handle(&handle) {
}
void dan::api::Engine::exit(int status) {
    // A REALLY BAD temporary solution
    exit(status);
}

void dan::api::Engine::open(sol::state_view &lua) {
    sol::usertype<Engine> type = lua.new_usertype<Engine>("Engine");

    type["exit"] = &exit;

}
