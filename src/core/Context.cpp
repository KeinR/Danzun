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

void dan::Context::setShader(const std::shared_ptr<Shader> &s) {
    if (currentShader != s) {
        currentShader = s;
        currentShader->doUse();
    }
}

void dan::Context::clearShader() {
    Shader::disuse();
    currentShader.reset();
}

void dan::Context::setViewport(int w, int h) {
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

dan::Shader &dan::Context::getShader() const {
    DANZUN_ASSERT(currentShader);
    return *currentShader;
}

dan::Engine &dan::Context::getEngine() const {
    DANZUN_ASSERT(engine != nullptr);
    return *engine;
}

// Static members

dan::Context &dan::Context::fromLua(sol::state_view lua) {
    return Engine::fromLua(lua).getContext();
}
