#include "Program.h"

#include <lua/lua.hpp>

#include "libs/engine.h"
#include "libs/game.h"
#include "libs/shader.h"
#include "libs/window.h"

dan::Program::Program(const Script &init): engine("Danzun", 500, 500), data(engine.getContext()) {
    vm.setProgram(*this);
    vm.exec(Script::fromFile("data/lua/init.lua"));
    vm.exec(init);
    // lua_State *L = vm.getHandle();

    vm.openLib("window", libs::window());
    vm.openLib("shader", libs::shader());

    vm.call("preInit");

    vm.openLib("engine", libs::engine());

    vm.call("init");
}
dan::Data &dan::Program::getData() {
    return data;
}
dan::Engine &dan::Program::getEngine() {
    return engine;
}
