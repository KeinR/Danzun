#include "util.h"

#include "../lib/opengl.h"
#include "../lib/audio.h"
#include "error.h"

std::string dan::ut::lowercase(const std::string &in) {
    std::string result = in;
    for (char &c : result) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    return result;
}

void dan::ut::checkGLError(const char *sig, sol::state_view lua) {
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) {
	err(sig, lua) << "OpenGL error: " << err::glErrStr(e);
    }
}

void dan::ut::checkALError(const char *sig, sol::state_view lua) {
    ALenum e = alGetError();
    if (e != AL_NO_ERROR) {
	err(sig, lua) << "OpenAL error: " << err::alErrStr(e);
    }
}

