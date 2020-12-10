#include "Engine.h"

#include "../lib/opengl.h"
#include "../lib/glfw.h"
#include "error.h"

#include "../loader/libs/engine.h"
#include "../loader/libs/game.h"
#include "../loader/libs/Shader.h"
#include "../loader/libs/window.h"
#include "../loader/libs/Mesh.h"
#include "../loader/libs/Image.h"

#include "EventCallback.h"

#include <iostream>

dan::Engine::Engine():
    window("Danzun", 500, 500, 0),
    rc(this),
    data(rc),
    windowEventCallback(nullptr),
    eventCallback(nullptr),
    game(*this),
    gameActive(false),
    gameSpeed(1)
{
    vm.setEngine(*this);
    window.setEventCallback(*this);
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
dan::Data &dan::Engine::getData() {
    return data;
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

dan::Context &dan::Engine::getContext() {
    return rc;
}

void dan::Engine::run() {
    window.makeCurrent();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    float start = glfwGetTime();
    float deltaTime = 0;

    while (!window.shouldClose()) {
        rc.setViewport(window.getWidth(), window.getHeight());
        glClearColor(0, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        vm.setGlobal("deltaTime", deltaTime);
        vm.call("main");

        window.swapBuffers();

        Window::pollEvents();

        const float time = glfwGetTime();
        deltaTime = (time - start) * gameSpeed;
        start = time;
        rc.getClock().pushDeltaTime(deltaTime);
        if (gameActive) {
            game.logic(deltaTime);
        }
        if (eventCallback != nullptr) {
            eventCallback->onFrame(*this, deltaTime);
        }
    }
}

void dan::Engine::open(const std::filesystem::path &filePath) {

    std::filesystem::path p = std::filesystem::absolute("../data/lua/game.lua");
    std::filesystem::path t = std::filesystem::absolute(filePath);

    // IMPORTANT: Set working directory to that of the init script
    // so that clients can use I/O sanely
    std::filesystem::current_path(filePath.parent_path());

    t = std::filesystem::relative(t);
    vm.execFile(t.string());

    std::cout << "start open windows" << '\n';

    vm.openLib(libs::window());
    vm.openLib(libs::shader());
    vm.openLib(libs::mesh());
    vm.openLib(libs::image());
    vm.openLib(libs::game());
    // api::window::open(s);
    // api::shader::open(s);
    // api::window::open(s);
    // api::window::open(s);
    // api::window::open(s);

    std::cout << "libs done" << '\n';

    vm.execFile(p.string());

    std::cout << "Setup done" << '\n';

    vm.call("preInit");

    std::cout << "Pre done" << '\n';

    vm.openLib(libs::engine());

    std::cout << "Engine opened" << '\n';

    window.setVisible(true);

    vm.call("init");

    vm.call("start");
}

void dan::Engine::start(const std::filesystem::path &filePath) {
    open(filePath);
    run();
}
