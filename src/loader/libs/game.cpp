#include "game.h"

#include <lua/lua.hpp>

#include "util.h"

static luaL_Reg funcs[] = {
    // {"echo", script_echo},
    // {"print", script_print},
    // {"setNode", script_setnode},
    // {"getString", script_getstring},
    // {"getChar", script_getchar},
    // {"exit", script_exit},
    {NULL, NULL}
};

dan::Lib dan::libs::game() {
    // TODO
}


