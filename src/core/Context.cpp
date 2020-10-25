#include "Context.h"

#include "debug.h"

#include "../Shader.h"

dan::Context::Context(Engine &e):
    engine(&e),
    currentShader(nullptr),
    fWidth(50),
    fHeight(50)
{
}

void dan::Context::setShader(Shader &s) {
    if (currentShader != &s) {
        currentShader = &s;
        currentShader->use();
    }
}

void dan::Context::clearShader() {
    currentShader = nullptr;
}

void dan::Context::setFWidth(int w) {
    fWidth = w;
}
void dan::Context::setFHeight(int h) {
    fHeight = h;
}

int dan::Context::getFWidth() const {
    return fWidth;
}
int dan::Context::getFHeight() const {
    return fHeight;
}

dan::Shader &dan::Context::getShader() const {
    DANZUN_ASSERT(currentShader != nullptr);
    return *currentShader;
}
dan::Engine &dan::Context::getEngine() const {
    DANZUN_ASSERT(engine != nullptr);
    return *engine;
}
