#include "error.h"

#include <stdexcept>
#include <iostream>

#include "../lib/opengl.h"

dan::err::err(const std::string &location, flag_t flags, bool throwOnDestruct):
    location(location), flags(flags), throwOnDestruct(throwOnDestruct)
{
    *this << '@' << location << ": ";
}
dan::err::~err() {
    if (throwOnDestruct) {
        raise();
    }
}

bool dan::err::getFlag(flag_t f) {
    return (flags & f) == f;
}

void dan::err::raise() {
    std::string message = str();
    if (getFlag(SEVERE)) {
        throw std::runtime_error("SEVERE: " + message);
    } else if (getFlag(WARNING)) {
        std::cerr << "\x1b[33mWARNING\x1b[00m: " << message << '\n';
    } else {
        std::cerr << "\x1b[31mERROR\x1b[00m: " << message << '\n';
    }
}

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
