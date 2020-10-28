#include "Engine.h"

#include "lib/opengl.h"

#include "core/error.h"

dan::Engine::Engine():
    window("Danzun", 500, 500, 0),
    rc(*this),
    scene(nullptr)
{
    window.setEventCallback(*this);
    gameTarget.setNode(game);

    setGameSize(400, 400);
}

void dan::Engine::setScene(Node &s) {
    scene = &s;
}

void dan::Engine::setGameSize(int w, int h) {
    game.setWidth(w);
    game.setHeight(h);
    gameTarget.setSize(w, h);
}

void dan::Engine::renderGameTarget() {
    gameTarget.render(rc);
}

void dan::Engine::bindGameTexture() {
    gameTarget.bindTexture();
}

void dan::Engine::run() {
    if (scene == nullptr) {
        err("Engine::run") << "No current scene!";
        return;
    }

    window.makeCurrent();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    while (!window.shouldClose()) {
        glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());
        glClearColor(0, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        scene->render(rc);

        window.swapBuffers();

        Window::pollEvents();
    }
}
