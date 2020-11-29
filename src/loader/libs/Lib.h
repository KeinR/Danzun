#ifndef DANZUN_LIB_LIB_H_INCLUDED
#define DANZUN_LIB_LIB_H_INCLUDED

namespace dan {
    struct Lib {
        const char *name;
        luaL_Reg *funcs;
        Lib(const char *name, luaL_Reg *funcs):
            name(name), funcs(funcs) {
        }
    };
}

#endif