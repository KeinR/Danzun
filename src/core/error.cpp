#include "error.h"

#include <stdexcept>
#include <iostream>

#include "opengl.h"

err::err(const std::string &location, bool severe): location(location), severe(severe) {
    *this << '@' << location << ": ";
}
err::~err() {
    doRaise();
}
void err::doRaise() {
    raise(str(), severe);
}

void err::raise(const std::string &message, bool severe) {
    if (severe) {
        throw std::runtime_error("SEVERE: " + message);
    } else {
        std::cerr << "Error: " << message << '\n';
    }
}

const char *err::glErrStr(int err) {
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
