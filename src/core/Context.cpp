#include "Context.h"

#include <array>

#include "debug.h"

#include "../Shader.h"
#include "../Engine.h"
#include "../lib/opengl.h"

dan::Context::Context(Engine &e):
    engine(&e),
    currentShader(nullptr),
    vWidth(50),
    vHeight(50)
{
    std::array<float, 16> v = {
        -1, -1, 0, 0,
        -1, 1, 0, 1,
        1, 1, 1, 1,
        1, -1, 1, 0
    };
    std::array<unsigned int, 6> i = {
        0, 1, 2,
        0, 2, 3
    };

    quad_.setIndices(i.size(), i.data());
    quad_.setVertices(v.size(), v.data());
    quad_.setParam(0, 2, 4, 0);
    quad_.setParam(1, 2, 4, 2);
}

void dan::Context::setShader(const shader_t &s) {
    DANZUN_ASSERT(s);
    if (currentShader != s) {
        currentShader = s;
        currentShader->use();
    }
}

void dan::Context::clearShader() {
    currentShader.reset();
    Shader::disuse();
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

const dan::Context::shader_t &dan::Context::getShader() const {
    DANZUN_ASSERT(currentShader);
    return currentShader;
}
dan::Engine &dan::Context::getEngine() const {
    DANZUN_ASSERT(engine != nullptr);
    return *engine;
}

void dan::Context::renderQuad() const {
    quad_.render();
}
