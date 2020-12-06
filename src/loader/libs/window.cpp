#include "window.h"

#include <map>
#include <string>

#include <lua/lua.hpp>

#include "util.h"
#include "../../core/Engine.h"
#include "../../win/Window.h"
#include "../../win/enums.h"

typedef dan::ScriptVM vm_t;

using namespace dan::libs::ut;

static int setTitle(lua_State *L);
static int setSize(lua_State *L);
static int setVisible(lua_State *L);
static int keyDown(lua_State *L);

static luaL_Reg funcs[] = {
    {"setTitle", setTitle},
    {"setSize", setSize},
    {"setVisible", setVisible},
    {"keyDown", keyDown},
    {NULL, NULL}
};

static std::map<std::string, dan::keyt> keyMappings;

static void initMappings();

dan::Lib dan::libs::window() {
    if (keyMappings.size() == 0) {
        initMappings();
    }
    return Lib("window", funcs);
}

int setTitle(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setTitle expects one string parameter");
    }
    std::string title = getString(L, 1);
    getEngine(L).getWindow().setTitle(title);
    return 0;
}

int setSize(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "setWidth expects two integer parameters");
    }
    int width = lua_tointeger(L, 1);
    int height = lua_tointeger(L, 2);
    getEngine(L).getWindow().setSize(width, height);
    return 0;
}

int setVisible(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "setVisible expects one boolean parameter");
    }
    bool visible = lua_toboolean(L, 1);
    getEngine(L).getWindow().setVisible(visible);
    return 0;
}

int keyDown(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "keyDown expects one boolean parameter");
    }
    std::string name = getString(L, 1);
    for (char &c : name) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    lua_pushboolean(L, getEngine(L).getWindow().keyPressed(keyMappings[name]));
    return 1;
}

void initMappings() {
    keyMappings["up"] = dan::keyt::UP;
    keyMappings["down"] = dan::keyt::DOWN;
    keyMappings["left"] = dan::keyt::LEFT;
    keyMappings["right"] = dan::keyt::RIGHT;
    keyMappings["esc"] = dan::keyt::ESCAPE;
    keyMappings["z"] = dan::keyt::Z;
    keyMappings["x"] = dan::keyt::X;
}
