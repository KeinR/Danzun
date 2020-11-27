#ifndef LIBS_UTIL_H_INCLUDED
#define LIBS_UTIL_H_INCLUDED

#include <string>

struct lua_State;
namespace dan {
    class ScriptVM;
    class Program;
}

namespace dan::libs::ut {
    std::string getString(lua_State *L, int index);
    ScriptVM &getVM(lua_State *L);
    Program &getProgram(lua_State *L);
}

#endif
