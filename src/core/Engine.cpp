#include "Engine.h"

#include "../lib/opengl.h"
#include "../lib/glfw.h"
#include "error.h"

#include "../api/Engine.h"
#include "../api/Game.h"
#include "../api/Player.h"
#include "../api/Window.h"

#include "../api/manifest.h"

#include "EventCallback.h"

#include <iostream>

// FPS counter
#include <chrono>
#include <thread>

#include <cmake/config.h>

dan::Engine::Engine():
    window("Danzun", 500, 500, 0),
    rc(this),
    windowEventCallback(nullptr),
    eventCallback(nullptr),
    game(*this)
{
    setMaxFPS(120);
    window.setEventCallback(*this);
    s.open_libraries(
        sol::lib::base,
        sol::lib::package,
        sol::lib::coroutine,
        sol::lib::string,
        sol::lib::os,
        sol::lib::math,
        sol::lib::table,
        sol::lib::bit32,
        sol::lib::io,
        sol::lib::ffi,
        sol::lib::jit
    );
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
sol::state_view dan::Engine::getState() {
    return s;
}

dan::Context &dan::Engine::getContext() {
    return rc;
}

void dan::Engine::setMaxFPS(float value) {
    maxFPS = value;
    frameInterval = 1.0f / maxFPS;
}
float dan::Engine::getMaxFPS() {
    return maxFPS;
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

// #define DANZUN_FPS_COUNTER 1

#ifdef DANZUN_FPS_COUNTER
    int sampleSize = 100;
    float secondsTaken = 0;
    int framesElapsed = 0;
    Window::setSwapInterval(0);
#endif

    while (!window.shouldClose()) {
        rc.setViewport(window.getWidth(), window.getHeight());
        glClearColor(0, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        s.collect_garbage();

        sol::function_result mr = s["main"].call();
        if (!mr.valid()) {
            sol::error serr = mr;
            err("Engine::run", s) << "Main loop failed: \"" << serr.what();
        }
        game.render(rc);

        window.swapBuffers();

        Window::pollEvents();

        float time;
        do {
            time = glfwGetTime();
            deltaTime = time - start;
        } while (deltaTime < frameInterval);

#ifdef DANZUN_FPS_COUNTER
        secondsTaken += deltaTime;
        framesElapsed++;
        if (framesElapsed > sampleSize) {
            std::cout << "-- FPS = " << (framesElapsed / secondsTaken) << '\n' << std::flush;
        }
#endif

        start = time;
        game.logic(deltaTime);
        if (eventCallback != nullptr) {
            eventCallback->onFrame(*this, deltaTime);
        }
    }
}

void dan::Engine::cCall(const std::string &functionGlobalName) {
    sol::function func = s[functionGlobalName];
    if (func.get_type() == sol::type::function) {
        sol::function_result result = func.call();
        if (!result.valid()) {
            sol::error serr = result;
            err("Engine::cCall") << "Init function failed: \"" << serr.what();
        }
    }
}

void dan::Engine::open(const std::filesystem::path &filePath) {

    std::filesystem::path t = std::filesystem::absolute(filePath);

    // IMPORTANT: Set working directory to that of the init script
    // so that clients can use I/O sanely
    std::filesystem::current_path(filePath.parent_path());

    sol::function_result result = s.script_file(filePath.filename().string());

    if (!result.valid()) {
        sol::error e = result;
        err("Engine:open") << "Error while executing init script \"" << filePath << "\": " << e.what();
    }

    // Register all the classes
    api::manifest::openAll(s);

    s["engine"] = api::Engine(*this);
    s["game"] = api::Game(game);
    s["player"] = api::Player(game.getPlayer());
    s["window"] = api::Window(window);

    cCall("preInit");

    window.setVisible(true);

    cCall("init");

    cCall("start");
}

void dan::Engine::start(const std::filesystem::path &filePath) {
    open(filePath);
    run();
}

// Static members

dan::Engine &dan::Engine::fromLua(sol::state_view lua) {
    api::Engine &engine = lua["engine"];
    return *engine.getHandle();
}
