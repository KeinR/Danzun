#include "engine.h"

#include <lua/lua.hpp>

#include "../Program.h"
#include "../ScriptVM.h"
#include "util.h"

static int getPath(lua_State *L);
static int loadImage(lua_State *L);
static int getPath(lua_State *L);
static int loadAseprite(lua_State *L);
static int loadShader(lua_State *L);
static int scriptExit(lua_State *L);

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static luaL_Reg funcs[] = {
    {"getPath", getPath},
    {"print", loadImage},
    {"setNode", loadAseprite},
    {"getString", loadShader},
    {"exit", scriptExit},
    {NULL, NULL}
};

dan::Lib dan::libs::engine() {
    Lib lib;
    lib.funcs = funcs;
    lib.len = sizeof(funcs) / sizeof(luaL_Reg) - 1;
    return lib;
}

int getPath(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "getPath expects one string parameter");
    }
    std::string result = getVM(L).getPath(getString(L, 1)).string();
    lua_pushstring(L, result.c_str());
    return 1;
}
int loadImage(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "loadImage expects one string parameter");
    }
    std::string name = getString(L, 1);
    std::string path = getString(L, 2);
    getProgram(L).getData().loadImage(name, path);
    return 0;
}
int loadAseprite(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "loadAseprite expects one string parameter");
    }
    std::string name = getString(L, 1);
    std::string path = getString(L, 2);
    getProgram(L).getData().loadAseprite(name, path);
    return 0;
}
int loadShader(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "loadShader expects one string parameter");
    }
    std::string name = getString(L, 1);
    std::string vert = getString(L, 2);
    std::string frag = getString(L, 3);
    getProgram(L).getData().loadShader(name, vert, frag);
    return 0;
}
int scriptExit(lua_State *L) {
    // Placeholder
}

