#include "Engine.h"

#include "../lib/opengl.h"
#include "../lib/glfw.h"
#include "error.h"

#include "EventCallback.h"

#include <iostream>
#include <chrono>
#include "../time/RealTimer.h"

dan::Engine::Engine(const std::string &winName, int width, int height):
    window(winName.c_str(), width, height, 0),
    rc(this),
    scene(nullptr),
    windowEventCallback(nullptr),
    eventCallback(nullptr),
    game(*this),
    gameActive(false),
    gameSpeed(1)
{
    window.setEventCallback(*this);
    gameTarget.setNode(game);

    setGameSize(400, 400);
}

bool dan::Engine::callbackCallable() {
    return windowEventCallback != nullptr;
}

void dan::Engine::keyPressed(const event::KeyPress &e) {
    if (callbackCallable()) {
        windowEventCallback->keyPressed(e);
    }
}
void dan::Engine::mouseMoved(const event::MouseMove &e) {
    if (callbackCallable()) {
        windowEventCallback->mouseMoved(e);
    }
}
void dan::Engine::mouseClicked(const event::MouseClick &e) {
    if (callbackCallable()) {
        windowEventCallback->mouseClicked(e);
    }
}
void dan::Engine::mouseScrolled(const event::MouseScroll &e) {
    if (callbackCallable()) {
        windowEventCallback->mouseScrolled(e);
    }
}
void dan::Engine::charInput(const event::CharInput &e) {
    if (callbackCallable()) {
        windowEventCallback->charInput(e);
    }
}

void dan::Engine::setWindowEventCallback(WindowEvent *e) {
    windowEventCallback = e;
}

void dan::Engine::setEventCallback(EventCallback *e) {
    eventCallback = e;
}

dan::Window &dan::Engine::getWindow() {
    return window;
}
dan::Game &dan::Engine::getGame() {
    return game;
}

void dan::Engine::setGameActive(bool flag) {
    gameActive = flag;
}
bool dan::Engine::isGameActive() const {
    return gameActive;
}

void dan::Engine::setGameSpeed(float s) {
    gameSpeed = s;
}
float dan::Engine::getGameSpeed() const {
    return gameSpeed;
}

void dan::Engine::setRefreshRate(int count) {
    glfwSwapInterval(count);
}

dan::Context &dan::Engine::getContext() {
    return rc;
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
    rc.setViewport(window.getWidth(), window.getHeight());
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

    float start = glfwGetTime();

    RealTimer post(500);
    post.start();
    float startTime = glfwGetTime();
    int frames = 0;

    while (!window.shouldClose()) {
        rc.setViewport(window.getWidth(), window.getHeight());
        glClearColor(0, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);


        scene->render(rc);

        window.swapBuffers();

        Window::pollEvents();

        const float time = glfwGetTime();
        const float deltaTime = (time - start) * gameSpeed;
        start = time;
        rc.getClock().pushDeltaTime(deltaTime);
        if (gameActive) {
            game.logic(deltaTime);
        }
        if (eventCallback != nullptr) {
            eventCallback->onFrame(*this, deltaTime);
        }

        frames++;
        if (post.done()) {
            std::cout << "FPS = " << (frames / (glfwGetTime() - startTime)) << '\n';
            frames = 0;
            post.start();
            startTime = glfwGetTime();
        }
    }
}
