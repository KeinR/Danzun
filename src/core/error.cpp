#include "error.h"

#include <stdexcept>
#include <iostream>

#include "../lib/opengl.h"
#include "../lib/audio.h"

dan::err::throwConf dan::err::throwConfig = dan::err::throwConf::SEVERE;

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
        message = "\x1b[31mSEVERE\x1b[00m: " + message;
        if (throwConfig == throwConf::ALL || throwConfig == throwConf::SEVERE) {
            throw std::runtime_error(message);
        } else {
            std::cerr << message << '\n';
        }
    } else if (getFlag(WARNING)) {
        message = "\x1b[33mWarning\x1b[00m: " + message;
        std::cerr << message << '\n';
    } else {
        message = "\x1b[31mError\x1b[00m: " + message;
        if (throwConfig == throwConf::ALL) {
            throw std::runtime_error(message);
        } else {
            std::cerr << message << '\n';
        }
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

const char *dan::err::alErrStr(int err) {
    switch (err) {
	case AL_INVALID_NAME: return "AL_INVALID_NAME";
	case AL_INVALID_ENUM: return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE: return "AL_INVALID_VALUE";
	case AL_INVALID_OPERATION: return "AL_INVALID_OPERATION";
	case AL_OUT_OF_MEMORY: return "AL_OUT_OF_MEMORY";
	default: return "-Unknown error-";
    }
}

std::string dan::err::trace(sol::state_view lua) {
    static const char *const errMsg = "[stack trace unavailable]";
    
    auto debug = lua["debug"];
    if (debug.get_type() == sol::type::nil) return errMsg;

    auto traceback = debug["traceback"];
    if (traceback.get_type() != sol::type::function) return errMsg;

    sol::function_result result = traceback.call();
    if (!result.valid()) {
        sol::error msg = result;
        return std::string("[Failed to obtain trace]: ") + msg.what();
    }

    return result.get<std::string>();
}

void dan::err::setThrowConfig(throwConf c) {
    throwConfig = c;
}
