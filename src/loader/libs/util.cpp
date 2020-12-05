#include "util.h"

#include <lua/lua.hpp>

#include <iostream>
#include <cmath>

#include "../ScriptVM.h"

std::string dan::libs::ut::getString(lua_State *L, int index) {
    std::size_t len;
    const char *data = lua_tolstring(L, index, &len);
    return std::string(data, len);
}

dan::ScriptVM &dan::libs::ut::getVM(lua_State *L) {
    return ::dan::ScriptVM::getVM(L);
}

dan::Engine &dan::libs::ut::getEngine(lua_State *L) {
    return getVM(L).getEngine();
}

int dan::libs::ut::getIntField(lua_State *L, int tableIndex, const char *name) {
    int type = lua_getfield(L, tableIndex, name);
    int result = std::floor(lua_tonumber(L, -1));
    lua_pop(L, 1);
    return result;
}
