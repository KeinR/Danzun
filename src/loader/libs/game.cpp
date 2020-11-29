#include "game.h"

#include <vector>
#include <utility>

#include <lua/lua.hpp>

#include "util.h"

#include "../../game/Game.h"
#include "../../game/Group.h"
#include "../../math/Polygon.h"
#include "../../math/Circle.h"
#include "../../math/Rectangle.h"

using namespace dan::libs::ut;

static int regCircleCol(lua_State *L);
static int regRectCol(lua_State *L);
static int regPolygonCol(lua_State *L);
static int testCollisions(lua_State *L);
static int resetGroups(lua_State *L);

static luaL_Reg funcs[] = {
    {"regCircleCol", regCircleCol},
    {"regRectCol", regRectCol},
    {"regPolygonCol", regPolygonCol},
    {"testCollisions", testCollisions},
    {"resetGroups", resetGroups},
    {NULL, NULL}
};

dan::Lib dan::libs::game() {
    return Lib("game", funcs);
}


int regCircleCol(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 4) {
        luaL_error(L, "regCircleCol expects 4 parameters");
    }
    std::string group = getString(L, 1);
    dan::Circle c;
    c.setX(lua_tonumber(L, 2));
    c.setY(lua_tonumber(L, 3));
    c.setRadius(lua_tonumber(L, 4));
    getProgram(L).getEngine().getGame().getGroup(group).pushCircle(c);
    return 0;
}
int regRectCol(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 4) {
        luaL_error(L, "regRectCol expects 5 parameters");
    }
    std::string group = getString(L, 1);
    getProgram(L).getEngine().getGame().getGroup(group).pushRectangle(dan::Rectangle(
        lua_tonumber(L, 2),
        lua_tonumber(L, 3),
        lua_tonumber(L, 4),
        lua_tonumber(L, 5)
    ));
    return 0;
}
int regPolygonCol(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 4) {
        luaL_error(L, "regPolygonCol expects at least 4 parameters");
    }
    std::string group = getString(L, 1);
    std::vector<float> points;
    points.reserve(top - 1);
    for (int i = 1; i <= top; i++) {
        points.push_back(lua_tonumber(L, i));
    }
    dan::Polygon p;
    p.setPoints(points);
    p.load();
    getProgram(L).getEngine().getGame().getGroup(group).pushPolygon(p);
    return 0;
}

int testCollisions(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "testCollisions expects 2 string parameters");
    }
    std::string first = getString(L, 1);
    std::string second = getString(L, 1);
    std::vector<std::pair<int,int>> result = getProgram(L).getEngine().getGame().testCollisions(first, second);

    const char *gameRegName = "_dan";
    const char *propName = "entityReg";

    lua_getglobal(L, gameRegName); // _dan
    lua_getfield(L, -1, propName); // _dan.entityReg

    for (std::pair<int,int> &p : result) {
        lua_geti(L, -1, p->first); // entitiyReg[firstId]
        lua_geti(L, -2, p->second); // entitiyReg[secondId]
        lua_getfield(L, -2, "hit"); // entitiyReg[firstId].hit(... ->
        lua_pushvalue(L, -3); // First param: self (entitiyReg[firstId])
        lua_pushvalue(L, -3); // Second param: other (entitiyReg[secondId])
        lua_call(L, 2, 0);
        lua_pop(L, 1); // Remove hit func

        // Same deal just with the other one
        lua_getfield(L, -1, "hit");
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -4);
        lua_call(L, 2, 0);
        lua_pop(L, 3); // Remove hit func, as well as the two objects
    }

    return 0;
}

int resetGroups(lua_State *L) {
    getProgram(L).getEngine().getGame().resetGroups();
    return 0;
}

