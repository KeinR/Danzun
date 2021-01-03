#include "Engine.h"

#include <sol/sol.hpp>

#include "../core/Engine.h"
#include "../core/error.h"
#include "../core/util.h"

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

void dan::api::Engine::setMaxFPS(float value) {
    handle->setMaxFPS(value);
}

void dan::api::Engine::toggleVSync(bool value) {
    ::dan::Window::setSwapInterval(value ? 1 : 0);
}

void dan::api::Engine::setThrowNever() {
    ::dan::err::setThrowConfig(::dan::err::throwConf::NEVER);
}
void dan::api::Engine::setThrowSevere() {
    ::dan::err::setThrowConfig(::dan::err::throwConf::SEVERE);
}
void dan::api::Engine::setThrowAll() {
    ::dan::err::setThrowConfig(::dan::err::throwConf::ALL);
}

float dan::api::Engine::getMaxFPS() {
    return handle->getMaxFPS();
}

void dan::api::Engine::setActiveTexture(sol::this_state l, unsigned int value) {
    glActiveTexture(GL_TEXTURE0 + value);
    ut::checkGLError("api::Engine", l);
}

void dan::api::Engine::open(sol::state_view &lua) {
    sol::usertype<Engine> type = lua.new_usertype<Engine>("Engine");

    type["exit"] = &Engine::term;
    type["getHandle"] = &Engine::getHandle;
    type["setThrowNever"] = &Engine::setThrowNever;
    type["setThrowSevere"] = &Engine::setThrowSevere;
    type["setThrowAll"] = &Engine::setThrowAll;

    type["vSync"] = sol::property(&Engine::toggleVSync);
    type["maxFPS"] = sol::property(&Engine::getMaxFPS, &Engine::setMaxFPS);

    type["setActiveTexture"] = &Engine::setActiveTexture;
}
