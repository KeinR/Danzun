#include "window.h"

#include <lua/lua.hpp>

#include "util.h"
#include "../Program.h"
#include "../../core/Engine.h"
#include "../../win/Window.h"

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static int setTitle(lua_State *L);
static int setSize(lua_State *L);
static int setVisible(lua_State *L);

static luaL_Reg funcs[] = {
    {"setTitle", setTitle},
    {"setSize", setSize},
    {"setVisible", setVisible},
    {NULL, NULL}
};

dan::Lib dan::libs::window() {
    return Lib("window", funcs);
}

int setTitle(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setTitle expects one string parameter");
    }
    std::string title = getString(L, 1);
    getProgram(L).getEngine().getWindow().setTitle(title);
    return 0;
}

int setSize(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "setWidth expects two integer parameters");
    }
    int width = lua_tointeger(L, 1);
    int height = lua_tointeger(L, 2);
    getProgram(L).getEngine().getWindow().setSize(width, height);
    return 0;
}

int setVisible(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setVisible expects one boolean parameter");
    }
    bool visible = lua_toboolean(L, 1);
    getProgram(L).getEngine().getWindow().setVisible(visible);
    return 0;
}
