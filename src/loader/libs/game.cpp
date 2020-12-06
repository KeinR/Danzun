#include "game.h"

#include <vector>
#include <utility>
#include <iostream>

#include <lua/lua.hpp>

#include "util.h"

#include "../../game/Game.h"
#include "../../game/Group.h"
#include "../../math/Polygon.h"
#include "../../math/Circle.h"
#include "../../core/Engine.h"

using namespace dan::libs::ut;

static int regCircleCol(lua_State *L);
static int regPolygonCol(lua_State *L);
static int testCollisions(lua_State *L);
static int resetGroups(lua_State *L);
static int getTime(lua_State *L);

static luaL_Reg funcs[] = {
    {"regCircleCol", regCircleCol},
    {"regPolygonCol", regPolygonCol},
    {"testCollisions", testCollisions},
    {"resetGroups", resetGroups},
    {"getTime", getTime},
    {NULL, NULL}
};

dan::Lib dan::libs::game() {
    return Lib("game", funcs);
}


int regCircleCol(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 5) {
        luaL_error(L, "regCircleCol expects 5 parameters");
    }
    // CALLBACK ID, group name, x (center), y (center), radius
    dan::Group::circle c;
    c.id = lua_tonumber(L, 1);
    std::string group = getString(L, 2);
    c.hitbox.setX(lua_tonumber(L, 3));
    c.hitbox.setY(lua_tonumber(L, 4));
    c.hitbox.setRadius(lua_tonumber(L, 5));
    getEngine(L).getGame().getGroup(group).pushCircle(c);
    return 0;
}
int regPolygonCol(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 4) {
        luaL_error(L, "regPolygonCol expects at least 5 parameters");
    }
    // CALLBACK ID, group name, x0, y0, x1, y1, x2, y2, ... 
    dan::Group::polygon p;
    p.id = lua_tonumber(L, 1);
    std::string group = getString(L, 2);
    std::vector<dan::Polygon::Point> points;
    points.reserve((top - 2) / 2);
    for (int i = 2; i+1 <= top; i += 2) {
        points.push_back(dan::Polygon::Point(
            lua_tonumber(L, i),
            lua_tonumber(L, i+1)
        ));
    }
    p.hitbox.setPoints(points);
    p.hitbox.load();
    getEngine(L).getGame().getGroup(group).pushPolygon(p);
    return 0;
}

int testCollisions(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "testCollisions expects 2 string parameters");
    }
    std::string first = getString(L, 1);
    std::string second = getString(L, 2);
    std::vector<std::pair<int,int>> result = getEngine(L).getGame().testCollisions(first, second);

    const char *gameRegName = "_dan";
    const char *propName = "entityReg";

    lua_getglobal(L, gameRegName); // _dan
    lua_getfield(L, -1, propName); // _dan.entityReg

    bool brk1 = false;
    bool brk2 = false;

    for (std::pair<int,int> &p : result) {
        brk1 = lua_geti(L, -1, p.first) == LUA_TNIL; // entitiyReg[firstId]
        brk2 = lua_geti(L, -2, p.second) == LUA_TNIL; // entitiyReg[secondId]

        if (brk1 || brk2) {
            std::cout << "BREAK" << '\n';
        }

        std::cout << "first -> " << p.first << '\n';
        std::cout << "second -> " << p.second << '\n';

        lua_getfield(L, -2, "hit"); // entitiyReg[firstId].hit(... ->
        std::cout << "ff" << '\n';
        lua_pushvalue(L, -3); // First param: self (entitiyReg[firstId])
        lua_pushvalue(L, -3); // Second param: other (entitiyReg[secondId])
        lua_call(L, 2, 0);

        std::cout << "dd" << '\n';

        // Same deal just with the other one
        lua_getfield(L, -1, "hit");
        std::cout << "ff2" << '\n';
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -4);
        lua_call(L, 2, 0);

        lua_pop(L, 2); // Remove the two objects
        std::cout << "top = " << lua_gettop(L) << '\n';
    }

    return 0;
}

int resetGroups(lua_State *L) {
    getEngine(L).getGame().resetGroups();
    return 0;
}

int getTime(lua_State *L) {
    lua_pushnumber(L, getEngine(L).getContext().getClock().getTime());
    return 1;
}

