#include "Program.h"

#include <lua/lua.hpp>

#include "libs/engine.h"
#include "libs/game.h"
#include "libs/Shader.h"
#include "libs/window.h"

dan::Program::Program(const Script &init): engine("Danzun", 500, 500), data(engine.getContext()) {
    vm.setProgram(*this);
    vm.exec(Script::fromFile("data/lua/init.lua"));
    vm.exec(init);
    // lua_State *L = vm.getHandle();

    vm.openLib(libs::window());
    vm.openLib(libs::shader());

    vm.call("preInit");

    vm.openLib(libs::engine());

    vm.call("init");

    vm.exec(Script::fromFile("data/lua/game.lua"));

    vm.call("run");
}
dan::Data &dan::Program::getData() {
    return data;
}
dan::Engine &dan::Program::getEngine() {
    return engine;
}
