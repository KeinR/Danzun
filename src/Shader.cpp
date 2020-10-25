#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <array>

#include "lib/opengl.h"
#include "core/debug.h"
#include "core/error.h"
#include "core/Context.h"

static constexpr unsigned int LOG_BUFFER_SIZE = 512;

/**
* Compiles the given shader and returns a handle to the OpenGL object.
* @param [in] type The type (GL_VERTEX_SHADER/GL_FRAGMENT_SHADER)
* @param [in] data Pointer to shader data
* @param [in] length Length of `data`
* @param [out] error String to dump errors. Untouched if no errors occurred.
* @return ID of the newly created shader object, or 0 on error [<a href="http://docs.gl/es3/glCreateShader">ref</a>]
*/
static GLuint compileShader(GLenum type, const char *data, int length);

/**
* Links two shaders (vertex and fragment) and returns the resulting
* shader program.
* @param [in] vertObject The vertex object
* @param [in] fragObject The fragment object
* @param [out] error String to dump errors. Untouched if no errors occurred.
* @return ID of the resulting shader program, or [undefined] on error (I don't see it specified anywhere in the docs(?))
*/
static GLuint linkShaders(GLuint vertObject, GLuint fragObject);

static char *loadFile(const std::string &path, int &length);

static void delShaders(GLuint vert, GLuint frag);

static const char *getShaderTypeName(GLenum type);

dan::Shader::Shader(const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength) {
    createShader(vertexData, vertexLength, fragmentData, fragmentLength);
}
dan::Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {

    int vertLen, fragLen;
    char *vertData = nullptr;
    char *fragData = nullptr;

    try {
        vertData = loadFile(vertexPath, vertLen);
        fragData = loadFile(fragmentPath, fragLen);
        createShader(vertData, vertLen, fragData, fragLen);
    } catch (std::exception &e) {
        if (vertData != nullptr) {
            delete[] vertData;
        }
        if (fragData != nullptr) {
            delete[] fragData;
        }
        err("dan::Shader::Shader(strings...)") << "Failed to load shader resource files: " << e.what();
    }

}
dan::Shader::~Shader() {
    free();
}

void dan::Shader::createShader(const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength) {
    #define FUNC_SIG "dan::Shader::createShader"
    #define FCLEAN delShaders(vertShader, fragShader)

    GLuint vertShader = 0;
    GLuint fragShader = 0;
    handle = 0;
    try {
        vertShader = compileShader(GL_VERTEX_SHADER, vertexData, vertexLength);
        fragShader = compileShader(GL_FRAGMENT_SHADER, fragmentData, fragmentLength);
        try {
            handle = linkShaders(vertShader, fragShader);
            FCLEAN;
        } catch (std::exception &e) {
            FCLEAN;
            err(FUNC_SIG) << "Failed to link shaders: " << e.what();
        }
    } catch (std::exception &e) {
        FCLEAN;
        err(FUNC_SIG) << "Failed to compile shaders: " << e.what();
    }

    #undef FCLEAN
    #undef FUNC_SIG
}

void dan::Shader::steal(Shader &other) {
    handle = other.handle;
    other.handle = 0;
}

dan::Shader::uniform_t dan::Shader::uni(const std::string &name) {
    #define FUNC_SIG "Shader::uni(const char*)"

    uniforms_t::iterator loc = uniforms.find(name);
    uniform_t location;
    if (loc == uniforms.end()) {
        // Cache miss
        GLenum error;
        error = glGetError();
        if (error != GL_NO_ERROR) {
            err(FUNC_SIG) << "OpenGL error BEFORE getting uniform location: " << err::glErrStr(error);
        }
        location = glGetUniformLocation(handle, name.c_str());
        uniforms[name] = location;
        error = glGetError();
        if (error != GL_NO_ERROR) {
            err(FUNC_SIG) << "OpenGL error AFTER getting uniform location: " << err::glErrStr(error);
        }
    } else {
        location = loc->second;
    }
    return location;

    #undef FUNC_SIG
}

void dan::Shader::free() {
    if (handle != 0) {
        glDeleteProgram(handle);
    }
}

void dan::Shader::use() const {
    glUseProgram(handle);
}

dan::Shader::uniform_t dan::Shader::getUniform(const std::string &name) {
    return uni(name);
}

dan::Shader::program_t dan::Shader::getHandle() const {
    return handle;
}

void dan::Shader::setMatrix4fv(Context &c, const std::string &name, const float *data) {
    c.setShader(*this);
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, data);
}
void dan::Shader::setInt1(Context &c, const std::string &name, int value) {
    c.setShader(*this);
    glUniform1i(getUniform(name), value);
}
void dan::Shader::set4fv(Context &c, const std::string &name, const float *values) {
    c.setShader(*this);
    glUniform4fv(getUniform(name), 1, values);
}

// Static members

void dan::Shader::disuse() {
    glUseProgram(0);
}

// Non-members

GLuint compileShader(GLenum type, const char *data, int length) {
    GLuint shader;
    shader = glCreateShader(type);
    // Load shader source code
    glShaderSource(shader, 1, &data, &length);
    // Compile code
    glCompileShader(shader);
    // Check for failure
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::array<char, LOG_BUFFER_SIZE> log;
        glGetShaderInfoLog(shader, log.size(), NULL, log.data());
        glDeleteShader(shader);
        std::string msg;
        msg += "[";
        msg += getShaderTypeName(type);
        msg += " shader]: \n";
        msg += log.data();
        throw std::runtime_error(msg);
    }
    return shader;
}

GLuint linkShaders(GLuint vertObject, GLuint fragObject) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertObject);
    glAttachShader(shaderProgram, fragObject);
    glLinkProgram(shaderProgram);
    // Check for failure
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::array<char, LOG_BUFFER_SIZE> log;
        glGetProgramInfoLog(shaderProgram, log.size(), NULL, log.data());
        glDeleteProgram(shaderProgram);
        throw std::runtime_error("\n " + std::string(log.data()));
    }
    return shaderProgram;
}

char *loadFile(const std::string &path, int &length) {
    std::ifstream file;
    // Ensure exception safety
    file.exceptions(std::ios::goodbit);

    file.open(path);
    if (!file.good()) {
        throw std::invalid_argument("Cannot open file \"" + path + "\"");
    }

    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);

    char *data = new char[length];

    file.read(data, length);

    if (!file.good()) {
        delete[] data;
        throw std::invalid_argument("Failed to read from file \"" + path + "\"");
    }

    return data;
}

void delShaders(GLuint vert, GLuint frag) {
    glDeleteShader(vert);
    glDeleteShader(frag);
}

const char *getShaderTypeName(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER: return "vertex";
        case GL_FRAGMENT_SHADER: return "fragment";
        default: return "unknown";
    }
}
