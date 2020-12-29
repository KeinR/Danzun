#include "Texture.h"

#include <cstddef>
#include <mutex>

#include "../lib/opengl.h"
#include "../core/Context.h"

// In-use enum values for Texture.
// def'd to be extra safe.
#define TEXTURE_TYPE GL_TEXTURE_2D
#define TEXTURE_PIXEL_TYPE GL_UNSIGNED_BYTE

// Default parameters.
constexpr dan::Texture::tparam dan::Texture::defaultParams{
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_EDGE,
    GL_LINEAR,
    GL_LINEAR
};

dan::Texture::Texture(Context &c): c(&c) {
    init(defaultParams);
}

dan::Texture::Texture(const tparam &param) {
    init(param);
}

dan::Texture::~Texture() {
    deInit();
}

void dan::Texture::init(const tparam &params) {
    std::lock_guard<Context> g(*c);
    glGenTextures(1, &buffer);
    setParams(params);
}

void dan::Texture::deInit() {
    std::lock_guard<Context> g(*c);
    glDeleteTextures(1, &buffer);
}

void dan::Texture::steal(Texture &other) {
    buffer = other.buffer;
    other.buffer = 0;
}

dan::Texture::Texture(Texture &&other) {
    steal(other);
}
dan::Texture &dan::Texture::operator=(Texture &&other) {
    steal(other);
    return *this;
}

void dan::Texture::setData(int fmt, unsigned int width, unsigned int height, const data_t *data) {
    std::lock_guard<Context> g(*c);
    bind();
    glTexImage2D(TEXTURE_TYPE, 0, fmt, width, height, 0, fmt, TEXTURE_PIXEL_TYPE, data);
    unbind();
}

unsigned int dan::Texture::getHandle() {
    return buffer;
}

void dan::Texture::bind() {
    std::lock_guard<Context> g(*c);
    glBindTexture(TEXTURE_TYPE, buffer);
}
void dan::Texture::unbind() {
    std::lock_guard<Context> g(*c);
    glBindTexture(TEXTURE_TYPE, 0);
}

void dan::Texture::clear() {
    std::lock_guard<Context> g(*c);
    bind();
    glTexImage2D(TEXTURE_TYPE, 0, GL_RED, 0, 0, 0, GL_RED, TEXTURE_PIXEL_TYPE, NULL);
    unbind();
}

void dan::Texture::setDefaultParams() {
    setParams(c, defaultParams);
}
void dan::Texture::setParams(const tparam &params) {
    std::lock_guard<Context> g(*c);
    bind();

    // x/y wrap parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_S, params.xWrap);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_T, params.yWrap);

    // min/max filtering parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MAG_FILTER, params.maxFilter);

    unbind();
}

int dan::Texture::getFormat(int channels) {
    switch (channels) {
        case 4: return GL_RGBA;
        case 3: return GL_RGB;
        case 2: return GL_RG;
        case 1: return GL_RED;
        default: return 0;
    }
}
