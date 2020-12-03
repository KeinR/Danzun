#ifndef DANZUN_LIBS_UTIL_H_INCLUDED
#define DANZUN_LIBS_UTIL_H_INCLUDED

#include <string>

struct lua_State;
namespace dan {
    class ScriptVM;
    class Engine;
}

namespace dan::libs::ut {
    std::string getString(lua_State *L, int index);
    ScriptVM &getVM(lua_State *L);
    Engine &getEngine(lua_State *L);
    int getIntField(lua_State *L, int tableIndex, const char *name);
}

#endif
