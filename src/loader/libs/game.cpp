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
static int loadPatterns(lua_State *L);

static luaL_Reg funcs[] = {
    {"regCircleCol", regCircleCol},
    {"regPolygonCol", regPolygonCol},
    {"testCollisions", testCollisions},
    {"resetGroups", resetGroups},
    {"getTime", getTime},
    {"loadPatterns", loadPatterns},
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

int loadPatterns(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "loadPattern expects 1 string parameter");
    }
    // Takes path, parses and adds pattern to registry, then returns a handle to that pattern
    // Can also lookup pattern later by name that it was set to

    std::string path = getString(L, 1);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path);
    if (result) {
        luaL_error(L, "File not found");
    }

    pugi::xml_node root = doc.first_child();

    dan::Game &game = getEngine(L).getGame();

    for (pugi::xml_node pattern : root.children("pattern")) {

        std::string name = pattern.attribute("name").value();

        std::vector<std::pair<std::string, float>> params;
        std::vector<std::pair<float, std::vector<std::pair<std::string, std::string>>>> exprs;

        for (pugi::xml_node run : pattern.children("run")) {
            std::pair<float, std::vector<std::string, std::string>> result;
            result.first = std::max(0, param.attribute("dur").as_float(0.0f));
            for (pugi::xml_node expr = run.first_child(); expr; expr = expr.next_sibling()) {
                result.second.emplace_back(expr.name(), expr.value());
            }
            exprs.push_back(std::move(result));
        }

        for (pugi::xml_node p : pattern.children("param")) {
            params.emplace_back(p.attribute("name").value(), p.attribute("value").as_float(0.0f));
        }

        game.addPattern(name, dan::Pattern(params, exprs));

    }

    return 0;
}

