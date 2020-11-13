#include "Engine.h"

#include "lib/opengl.h"
#include "lib/glfw.h"
#include "core/error.h"

#include "EventCallback.h"

#include <iostream>
#include <chrono>
#include "RealTimer.h"

dan::Engine::Engine(const std::string &winName, int width, int height):
    window(winName.c_str(), width, height, 0),
    rc(this),
    scene(nullptr),
    windowEventCallback(nullptr),
    eventCallback(nullptr),
    gameActive(false),
    gameSpeed(1)
{
    window.setEventCallback(*this);
    gameTarget.setNode(game);

    setGameSize(400, 400);
}

void dan::Engine::keyPressed(int key, int action, int mods) {
    if (windowEventCallback != nullptr) {
        windowEventCallback->keyPressed(key, action, mods);
    }
}
void dan::Engine::mouseMoved(float mouseX, float mouseY) {
    if (windowEventCallback != nullptr) {
        windowEventCallback->mouseMoved(mouseX, mouseY);
    }
}
void dan::Engine::mouseClicked(int button, bool pressed, int mods) {
    if (windowEventCallback != nullptr) {
        windowEventCallback->mouseClicked(button, pressed, mods);
    }
}
void dan::Engine::mouseScrolled(double xOffset, double yOffset) {
    if (windowEventCallback != nullptr) {
        windowEventCallback->mouseScrolled(xOffset, yOffset);
    }
}
void dan::Engine::charInput(unsigned int codepoint) {
    if (windowEventCallback != nullptr) {
        windowEventCallback->charInput(codepoint);
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
