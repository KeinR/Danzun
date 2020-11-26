#include "ScriptVM.h"

#include <map>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../core/debug.h"

#include "Script.h"

void defaultErrCallback(dan::ScriptVM &vm, const std::string &msg) {
    std::clog << "LUA VM ERROR [0x" << std::hex << &vm << std::dec << "]:" << msg << '\n';
}

typedef std::map<lua_State*,ScriptVM*> vms_t;

static vms_t vms;

dan::ScriptVM::ScriptVM():
    errCallback(defaultErrCallback),
    workingDir(".")
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

void dan::ScriptVM::steal(ScriptVM &other) {
    L = other.L;
    other.L = nullptr;
    vms[L] = this;
    errCallback = other.errCallback;
    workingDir = other.workingDir;
}

void dan::ScriptVM::free() {
    if (L != nullptr) {
        vms.erase(L);
        lua_close(L);
    }
}

bool eng::ScriptVM::checkState(int code) {
    DANZUN_ASSERT(errCallback);

    if (code != LUA_OK) {
        errCallback(lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }
    return true;
}

void dan::ScriptVM::setErrCallback(const errorCallback_t &callback) {
    errorCallback = callback;
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

void dan::ScriptVM::setWorkingDir(const std::filesystem::path &path) {
    workingDir = path;
}

std::filesystem::path dan::ScriptVM::getWorkingDir() {
    return workingDir;
}

void dan::ScriptVM::exec(const Script &script) {
    currentScript = &script;
    int status = luaL_dostring(L, script.getCode().c_str());
    currentScript = nullptr;

    if (status != LUA_OK) {
        std::stringstream str;
        str << "ScriptVM err @" << this << ": " << lua_tostring(L, -1);
        lua_pop(L, 1);
        throw std::logic_error(str.str());
    }
}

void dan::ScriptVM::exec(const Script &script) {
    setWorkingDir(script.getDir());
    exec(script.getCode());
}

dan::ScriptVM &dan::ScriptVM::getVM(lua_State *L) {
    vms_t::iterator it = vms.find(L);

    DANZUN_ASSERT(it != vms.end());

    return *it->second;
}
