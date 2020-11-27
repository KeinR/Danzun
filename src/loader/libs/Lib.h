#ifndef DANZUN_LIB_H_INCLUDED
#define DANZUN_LIB_H_INCLUDED

struct luaL_Reg;

namespace dan {
    struct Lib {
        luaL_Reg *funcs;
        int len;
    };
}

#endif
