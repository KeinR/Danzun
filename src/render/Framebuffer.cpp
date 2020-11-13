#include "Framebuffer.h"

#include "Texture.h"

#include "../lib/opengl.h"

dan::Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &handle);
}
dan::Framebuffer::Framebuffer(Framebuffer &&other) {
    steal(other);
}
dan::Framebuffer::~Framebuffer() {
    free();
}
dan::Framebuffer &dan::Framebuffer::operator=(Framebuffer &&other) {
    free();
    steal(other);
    return *this;
}

void dan::Framebuffer::steal(Framebuffer &other) {
    handle = other.handle;
    other.handle = 0;
}

void dan::Framebuffer::free() {
    if (handle != 0) {
        glDeleteFramebuffers(1, &handle);
    }
}

void dan::Framebuffer::attachTexture(Texture &tex) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.getHandle(), 0);
}

void dan::Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

// Static member

void dan::Framebuffer::bindDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
