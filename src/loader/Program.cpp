#include "Program.h"

#include <lua/lua.hpp>

#include "libs/engine.h"
#include "libs/game.h"
#include "libs/shader.h"
#include "libs/window.h"

dan::Program::Program(const Script &init): engine("Danzun", 500, 500) {
    vm.setProgram(*this);
    vm.exec(Script::fromFile("data/lua/init.lua"));
    vm.exec(init);
    lua_State *L = vm.getHandle();
    lua_newtable(L);
    luaL_setfuncs(L, libs::window(), 0);
    lua_setglobal(L, "window");
    lua_getglobal(L, "preInit");
    lua_call(L, 0, 0);
}
dan::Data &dan::Program::getData() {
    return data;
}
dan::Engine &dan::Program::getEngine() {
    return engine;
}
