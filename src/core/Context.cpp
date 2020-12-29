#include "Context.h"

#include "debug.h"
#include "Engine.h"

#include "../render/Shader.h"
#include "../lib/opengl.h"

dan::Context::Context(Engine *e):
    engine(e),
    currentShader(nullptr),
    vWidth(50),
    vHeight(50)
{
}

void dan::Context::setShader(Shader &s) {
    std::lock_guard<Context> g(*this);
    if (currentShader != &s) {
        currentShader = &s;
        s.doUse();
    }
}

void dan::Context::clearShader() {
    std::lock_guard<Context> g(*this);
    currentShader = nullptr;
    Shader::disuse();
}

void dan::Context::setViewport(int w, int h) {
    std::lock_guard<Context> g(*this);
    vWidth = w;
    vHeight = h;
    glViewport(0, 0, vWidth, vHeight);
}

int dan::Context::getVPWidth() const {
    return vWidth;
}
int dan::Context::getVPHeight() const {
    return vHeight;
}

void dan::Context::lock() {
    engine->lockContext();
}
void dan::Context::unlock() {
    engine->unlockContext();
}

dan::Shader &dan::Context::getShader() const {
    DANZUN_ASSERT(currentShader != nullptr);
    return *currentShader.load();
}

dan::Engine &dan::Context::getEngine() const {
    DANZUN_ASSERT(engine != nullptr);
    return *engine;
}

// Static members

dan::Context &dan::Context::fromLua(sol::state_view lua) {
    return Engine::fromLua(lua).getContext();
}
