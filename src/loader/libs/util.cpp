#include "util.h"

#include <lua/lua.hpp>

#include "../ScriptVM.h"

std::string dan::libs::ut::getString(lua_State *L, int index) {
    std::size_t len;
    const char *data = lua_tolstring(L, index, &len);
    return std::string(data, len);
}

dan::ScriptVM &dan::libs::ut::getVM(lua_State *L) {
    return ::dan::ScriptVM::getVM(L);
}

dan::Program &dan::libs::ut::getProgram(lua_State *L) {
    return getVM(L).getProgram();
}
