#include "Framebuffer.h"

#include "../lib/opengl.h"
#include "../core/error.h"
#include "../core/Engine.h"
#include "../core/Context.h"

dan::api::Framebuffer::Framebuffer(sol::this_state l, int width, int height):
    width(width), height(height)
{
    tex.reserve(GL_RGBA, width, height);
    buf.attachTex(tex);
    if (!buf.complete()) {
        err("api::Framebuffer", l) << "Framebuffer is not complete";
    }
}

void dan::api::Framebuffer::bindBuf(sol::this_state l) {
    buf.bind();
    Context &c = Context::fromLua(l);
    c.setViewport(width, height);
}

void dan::api::Framebuffer::unbindBuf(sol::this_state l) {
    ::dan::Framebuffer::bindDefault();
    Engine &e = Engine::fromLua(l);
    e.getContext().setViewport(e.getWindow().getWidth(), e.getWindow().getHeight());
}

void dan::api::Framebuffer::bindTex() {
    tex.bind();
}

void dan::api::Framebuffer::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void dan::api::Framebuffer::open(sol::state_view lua) {
   sol::usertype<Framebuffer> type = lua.new_usertype<Framebuffer>("Framebuffer",
        sol::constructors<Framebuffer(sol::this_state,int,int)>()
    );
    
    type["bindBuf"] = &Framebuffer::bindBuf;
    type["unbindBuf"] = &Framebuffer::unbindBuf;
    type["bindTex"] = &Framebuffer::bindTex;
    type["clear"] = &Framebuffer::clear;

}

