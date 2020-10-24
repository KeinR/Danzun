#include "Texture.h"

#include "ManImage.h"
#include "Image.h"
#include "opengl.h"
#include "error.h"

// In-use enum values for Texture.
// def'd to be extra safe.
#define TEXTURE_TYPE GL_TEXTURE_2D
#define TEXTURE_PIXEL_TYPE GL_UNSIGNED_BYTE

// Default parameters.
constexpr dan::Texture::tparam dan::Texture::defaultParams{
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_EDGE,
    GL_NEAREST,
    GL_NEAREST
};

dan::Texture::Texture() {
    init(defaultParams);
}

dan::Texture::Texture(const tparam &param) {
    init(param);
}

dan::Texture::~Texture() {
    deInit();
}

void dan::Texture::init(const tparam &params) {
    glGenTextures(1, &buffer);
    setParams(params);
    iWidth = 0;
    iHeight = 0;
}

void dan::Texture::deInit() {
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

unsigned int dan::Texture::getHandle() {
    return buffer;
}

void dan::Texture::bind() const {
    glBindTexture(TEXTURE_TYPE, buffer);
}
void dan::Texture::unbind() {
    glBindTexture(TEXTURE_TYPE, 0);
}

void dan::Texture::loadImage(const std::string &imgPath, bool flipOnLoad) {
    ManImage img(imgPath, flipOnLoad);
    setImage(img);
}

void dan::Texture::setImage(const Image &image) {
    GLenum f;
    switch (image.getChannels()) {
        case 4: f = GL_RGBA; break;
        case 3: f = GL_RGB; break;
        case 2: f = GL_RG; break;
        case 1: f = GL_RED; break;
        default:
            err::raise(err::INVALID_ARG, "dan::Texture::setImage(const Image&)", "Invalid image channels");
            return;
    }

    bind();
    glTexImage2D(TEXTURE_TYPE, 0, f, image.getWidth(), image.getHeight(), 0, f, TEXTURE_PIXEL_TYPE, image.getData());
    unbind();

    iWidth = image.getWidth();
    iHeight = image.getHeight();
}

void dan::Texture::setData(format fmt, unsigned int width, unsigned int height, const data_t *data) {
    GLenum f;
    switch (fmt) {
        case RGBA: f = GL_RGBA; break;
        case RGB: f = GL_RGB; break;
        case RG: f = GL_RG; break;
        case RED: f = GL_RED; break;
        case INVALID_FORMAT: // Fallthrough
        default:
            err::raise(err::INVALID_ARG, "dan::Texture::setData(format,unsigned int,unsigned int,const data_t*)", "Invalid format enum");
            return;
    }

    bind();
    glTexImage2D(TEXTURE_TYPE, 0, f, width, height, 0, f, TEXTURE_PIXEL_TYPE, data);
    unbind();

    iWidth = width;
    iHeight = height;
}

void dan::Texture::setData(int channels, unsigned int width, unsigned int height, const data_t *data) {
    format f = getFormat(channels);
    if (f == INVALID_FORMAT) {
        err::raise(err::INVALID_ARG, "dan::Texture::setData(int,unsigned int,unsigned int,const data_t*)", "Invalid number of channels");
    }
    setData(f, width, height, data);
}

void dan::Texture::clear() {
    bind();
    glTexImage2D(TEXTURE_TYPE, 0, GL_RED, 0, 0, 0, GL_RED, TEXTURE_PIXEL_TYPE, NULL);
    unbind();

    iWidth = 0;
    iHeight = 0;
}

void dan::Texture::genMipmap() {
    bind();
    glGenerateMipmap(TEXTURE_TYPE);
    unbind();
}

void dan::Texture::setDefaultParams() {
    setParams(defaultParams);
}
void dan::Texture::setParams(const tparam &params) {
    bind();

    // x/y wrap parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_S, params.xWrap);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_WRAP_T, params.yWrap);

    // min/max filtering parameter
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MIN_FILTER, params.minFilter);
    glTexParameteri(TEXTURE_TYPE, GL_TEXTURE_MAG_FILTER, params.maxFilter);

    unbind();
}

int dan::Texture::getWidth() {
    return iWidth;
}
int dan::Texture::getHeight() {
    return iHeight;
}

dan::Texture::format dan::Texture::getFormat(int channels) {
    switch (channels) {
        case 4: return format::RGBA;
        case 3: return format::RGB;
        case 2: return format::RG;
        case 1: return format::RED;
        default: return format::INVALID_FORMAT;
    }
}
