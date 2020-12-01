#include "engine.h"

#include <lua/lua.hpp>

#include "../Program.h"
#include "../ScriptVM.h"
#include "util.h"

static int getPath(lua_State *L);
static int setWorkingFile(lua_State *L);
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
    // Placeholder
    exit(0);
    return 0;
}

