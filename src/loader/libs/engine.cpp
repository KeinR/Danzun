#include "engine.h"

#include <lua/lua.hpp>

// Temp
#include <iostream>

#include "../Program.h"
#include "../ScriptVM.h"
#include "util.h"

static int getPath(lua_State *L);
static int setWorkingDir(lua_State *L);
static int setWorkingFile(lua_State *L);
static int getWorkingDir(lua_State *L);
static int scriptExit(lua_State *L);

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static luaL_Reg funcs[] = {
    {"getPath", getPath},
    {"setWorkingDir", setWorkingDir},
    {"setWorkingFile", setWorkingFile},
    {"getWorkingDir", getWorkingDir},
    {"exit", scriptExit},
    {NULL, NULL}
};

dan::Lib dan::libs::engine() {
    return Lib("engine", funcs);
}

int getPath(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "getPath expects 1 string parameter");
    }
    std::string result = getVM(L).getPath(getString(L, 1)).string();
    std::cout << "working dir = " << getVM(L).getWorkingDir() << '\n';
    std::cout << "given string = " << getString(L, 1) << '\n';
    std::cout << "resultant path = " << result << '\n';
    lua_pushstring(L, result.c_str());
    return 1;
}

int setWorkingDir(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setWorkingDir expects 1 string parameter");
    }
    std::string path = getString(L, 1);
    getVM(L).setWorkingDir(path);
    return 0;
}

int setWorkingFile(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setWorkingFile expects 1 string parameter");
    }
    std::string path = getString(L, 1);
    getVM(L).setWorkingDir(std::filesystem::path(path).parent_path());
    return 0;
}

int getWorkingDir(lua_State *L) {
    lua_pushstring(L, getVM(L).getWorkingDir().string().c_str());
    return 1;
}

int scriptExit(lua_State *L) {
    // Placeholder
    return 0;
}

