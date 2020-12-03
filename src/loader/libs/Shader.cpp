#include "Shader.h"

#include <lua/lua.hpp>

#include <iostream>

#include "util.h"
#include "../../render/Shader.h"
#include "../ScriptVM.h"
#include "../../core/debug.h"
#include "../../core/Engine.h"

static const char *const metatable = "Shader";

struct Shader {
    int id;
};

static int script_new(lua_State *L);
static int setInt(lua_State *L);
static int set(lua_State *L);
static int use(lua_State *L);
static int gc(lua_State *L);

static dan::Shader &getShader(lua_State *L, int index);

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static luaL_Reg funcs[] = {
    {"new", script_new},
    {"setInt", setInt},
    {"set", set},
    {"use", use},
    {"__gc", gc},
    {NULL, NULL}
};

dan::Lib dan::libs::shader() {
    return Lib(metatable, funcs);
}

dan::Shader &getShader(lua_State *L, int index) {
    // TODO: Type safety
    Shader *sh = (Shader *)lua_touserdata(L, index);
    return getEngine(L).getData().getShader(sh->id);
}

int script_new(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "new expects at least 2 arguments");
    }
    std::string vert = getString(L, 1);
    std::string frag = getString(L, 2);

    Shader *s = (Shader *)lua_newuserdatauv(L, sizeof(Shader), 0);
    s->id = getEngine(L).getData().loadShader(vert, frag);

    lua_getglobal(L, metatable);
    lua_setmetatable(L, -2);
    return 1;
}

int setInt(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 3 || top > 6) {
        luaL_error(L, "shader:setInt expects at least 3 arguments and no more than 6");
    }
    dan::Shader &s = getShader(L, 1);
    std::string name = getString(L, 2);

    int count = top - 2;
    switch (count) {
        case 1:
            s.setInt1(name, lua_tointeger(L, 3));
            std::cout << "  SET INT " << name << '\n';
            break;
        case 2:
            // s->setInt2(name, lua_tointeger(L, 4));
            break;
        case 3:
            // s->setInt3(name, lua_tointeger(L, 5));
            break;
        case 4:
            // s->setInt4(name, lua_tointeger(L, 6));
            break;
        default:
            DANZUN_ASSERT(false); // Unreachable
            break;
    }
    return 0;
}

int set(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 3) {
        luaL_error(L, "set expects at least 3 arguments");
    }
    dan::Shader &s = getShader(L, 1);
    std::string name = getString(L, 2);

    int count = top - 2;
    switch (count) {
        case 1:
            // s->setFloat1(name, lua_tointeger(L, 3));
            break;
        case 2:
            // s->setFloat2(name, lua_tointeger(L, 3));
            break;
        case 3:
            // s->setFloat3(name, lua_tointeger(L, 3));
            break;
        case 4:
            // s->setFloat4(name, lua_tointeger(L, 3));
            break;
        default:
            luaL_error(L, "shader:set expects at minimum 1 and at max 3 uniform values");
            break;
    }
    return 0;
}

int use(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "use expects 1 argument");
    }
    dan::Shader &s = getShader(L, 1);
    s.doUse();
    return 0;
}

int gc(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "__gc expects 1 argument");
    }
    Shader *sh = (Shader *)luaL_checkudata(L, 1, metatable);
    getEngine(L).getData().deleteShader(sh->id);
    return 0;
}

