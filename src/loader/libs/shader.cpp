#include "shader.h"

#include <lua/lua.hpp>

#include "util.h"
#include "../../render/Shader.h"
#include "../ScriptVM.h"

static int setInt(lua_State *L);
static int set(lua_State *L);

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static luaL_Reg funcs[] = {
    {"setInt", setInt},
    {"set", set},
    {NULL, NULL}
};

luaL_Reg *dan::libs::shader() {
    return funcs;
}

int setInt(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 3) {
        luaL_error(L, "shader:setInt expects at least 3 arguments");
    }
    dan::Shader *s = (dan::Shader *)lua_touserdata(L, 1);
    std::string name = getString(L, 2);

    int count = top - 2;
    switch (count) {
        case 1:
            s->setInt1(name, lua_tointeger(L, 3));
            break;
        case 2:
            // s->setInt2(name, lua_tointeger(L, 3));
            break;
        case 3:
            // s->setInt3(name, lua_tointeger(L, 3));
            break;
        case 4:
            // s->setInt4(name, lua_tointeger(L, 3));
            break;
        default:
            luaL_error(L, "shader:setInt expects at minimum 1 and at max 3 uniform values");
            break;
    }
    return 0;
}

int set(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 3) {
        luaL_error(L, "shader:set expects at least 3 arguments");
    }
    dan::Shader *s = (dan::Shader *)lua_touserdata(L, 1);
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
