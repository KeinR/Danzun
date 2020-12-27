#include "error.h"

#include <stdexcept>
#include <iostream>

#include "../lib/opengl.h"

dan::err::err(const std::string &location, sol::state_view lua, flag_t flags):
    err(location, &lua, flags) {
}
dan::err::err(const std::string &location, flag_t flags):
    err(location, nullptr, flags) {
}
dan::err::err(const std::string &location, sol::state_view *lua, flag_t flags):
    location(location), flags(flags)
{
    *this << '@' << location << ": ";
    if (lua != nullptr) {
        stackTrace = "\n" + trace(*lua);
    }
}
dan::err::~err() {
    if (!getFlag(NOTHROW)) {
        raise();
    }
}

bool dan::err::getFlag(flag_t f) {
    return (flags & f) == f;
}

void dan::err::raise() {
    std::string message = str() + stackTrace;
    if (getFlag(SEVERE)) {
        throw std::runtime_error("SEVERE: " + message);
    } else if (getFlag(WARNING)) {
        std::cerr << "\x1b[33mWARNING\x1b[00m: " << message << '\n';
    } else {
        std::cerr << "\x1b[31mERROR\x1b[00m: " << message << '\n';
    }
}

// Static members

const char *dan::err::glErrStr(int err) {
    switch (err) {
        case GL_NO_ERROR: return "GL_NO_ERROR";
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        default: return "-Unknown error-";
    }
}

std::string dan::err::trace(sol::state_view lua) {
    static const char *const errMsg = "[stack trace unavailable]";
    
    sol::table debug = lua["debug"];
    if (debug.get_type() == sol::type::nil) return errMsg;

    sol::function traceback = debug["traceback"];
    if (traceback.get_type() == sol::type::nil) return errMsg;

    sol::function_result result = traceback.call();
    if (!result.valid()) {
        sol::error msg = result;
        return msg.what();
    }

    return result.get<std::string>();
}
