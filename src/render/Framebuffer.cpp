#include "Framebuffer.h"

#include "Texture.h"
#include "../lib/opengl.h"

dan::Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &handle);
}

dan::Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &handle);
}

void dan::Framebuffer::attachTex(Texture &tex) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.getHandle(), 0);
    bindDefault();
}

bool dan::Framebuffer::complete() {
    bind();
    bool comp = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    bindDefault();
    return comp;
}

void dan::Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void dan::Framebuffer::bindDefault() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


