#include "debug.h"

#include <iostream>
#include "../lib/opengl.h"

#include "error.h"

bool dan::db::checkGLError() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "GL_ERROR: " << getGLErrorStr(error) << '\n';
        return true;
    }
    return false;
}
const char *dan::db::getGLErrorStr(int error) {
    return err::glErrStr(error);
}
