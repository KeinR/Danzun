#include "engine.h"

#include <lua/lua.hpp>

#include "util.h"

static int scriptExit(lua_State *L);

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static luaL_Reg funcs[] = {
    {"exit", scriptExit},
    {NULL, NULL}
};

dan::Lib dan::libs::engine() {
    return Lib("engine", funcs);
}

int scriptExit(lua_State *L) {
    // Placeholder, should gracefuly exit
    exit(0);
    return 0;
}
