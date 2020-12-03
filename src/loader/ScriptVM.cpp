#include "ScriptVM.h"

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <lua/lua.hpp>

#include "../core/debug.h"
#include "libs/Lib.h"

void defaultErrCallback(dan::ScriptVM &vm, const std::string &msg) {
    std::clog << "LUA VM ERROR [0x" << std::hex << &vm << std::dec << "]:" << msg << '\n';
}

typedef std::unordered_map<lua_State*,dan::ScriptVM*> vms_t;

static vms_t vms;

dan::ScriptVM::ScriptVM():
    L(nullptr),
    engine(nullptr),
    errCallback(defaultErrCallback)
{

    L = luaL_newstate();
    if (L == NULL) {
        throw std::runtime_error("ScriptVM: luaL_newstate failed");
    }

    luaL_openlibs(L);
 
    vms[L] = this;
}
dan::ScriptVM::ScriptVM(ScriptVM &&other) {
    steal(other);
}
dan::ScriptVM::~ScriptVM() {
    free();
}
dan::ScriptVM &dan::ScriptVM::operator=(ScriptVM &&other) {
    free();
    steal(other);
    return *this;
}

lua_State *dan::ScriptVM::getHandle() {
    return L;
}

void dan::ScriptVM::steal(ScriptVM &other) {
    L = other.L;
    other.L = nullptr;
    vms[L] = this;
    errCallback = other.errCallback;
}

void dan::ScriptVM::free() {
    if (L != nullptr) {
        vms.erase(L);
        lua_close(L);
    }
}

bool dan::ScriptVM::checkState(int code) {
    DANZUN_ASSERT(errCallback);

    if (code != LUA_OK) {
        errCallback(*this, lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }
    return true;
}

void dan::ScriptVM::setEngine(Engine &e) {
    engine = &e;
}

dan::Engine &dan::ScriptVM::getEngine() {
    DANZUN_ASSERT(engine != nullptr);
    return *engine;
}

void dan::ScriptVM::setErrCallback(const errCallback_t &callback) {
    errCallback = callback;
}

void dan::ScriptVM::setGlobal(const std::string &name, const std::string &val) {
    lua_pushstring(L, val.c_str());
    lua_setglobal(L, name.c_str());
}
void dan::ScriptVM::setGlobal(const std::string &name, float val) {
    lua_pushnumber(L, val);
    lua_setglobal(L, name.c_str());
}
void dan::ScriptVM::setGlobal(const std::string &name, int val) {
    lua_pushinteger(L, val);
    lua_setglobal(L, name.c_str());
}

void dan::ScriptVM::openLib(const Lib &lib) {
    // TODO: Keep track of # funcs so that can reserve table space
    lua_newtable(L);
    luaL_setfuncs(L, lib.funcs, 0);
    lua_setglobal(L, lib.name);
    lua_getglobal(L, lib.name);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_newmetatable(L, lib.name);
    // lua_pop(L, 1);
}

void dan::ScriptVM::closeLib(const Lib &lib) {
    // Just set it to nil
    lua_pushnil(L);
    lua_setglobal(L, lib.name);
}

void dan::ScriptVM::call(const std::string &name) {
    lua_getglobal(L, name.c_str());
    int result = lua_pcall(L, 0, 0, 0);
    if (result != LUA_OK) {
        throw std::logic_error(lua_tostring(L, -1));
    }
}

void dan::ScriptVM::exec(const std::string &code) {
    int status = luaL_dostring(L, code.c_str());

    if (status != LUA_OK) {
        std::stringstream str;
        str << "ScriptVM err @" << this << ": " << lua_tostring(L, -1);
        lua_pop(L, 1);
        throw std::logic_error(str.str());
    }
}

void dan::ScriptVM::execFile(const std::string &path) {
    int status = luaL_dofile(L, path.c_str());

    if (status != LUA_OK) {
        std::stringstream str;
        str << "ScriptVM err @" << this << ": " << lua_tostring(L, -1);
        lua_pop(L, 1);
        throw std::logic_error(str.str());
    }
}

dan::ScriptVM &dan::ScriptVM::getVM(lua_State *L) {
    vms_t::iterator it = vms.find(L);

    DANZUN_ASSERT(it != vms.end());

    return *it->second;
}
