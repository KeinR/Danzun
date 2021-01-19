#include "Engine.h"

#include "../lib/opengl.h"
#include "../lib/glfw.h"
#include "error.h"

#include "../api/Engine.h"
#include "../api/Game.h"
#include "../api/Player.h"
#include "../api/Window.h"

#include "../api/manifest.h"

#include <iostream>

// FPS counter
#include <chrono>
#include <thread>

#include <cmake/config.h>

dan::Engine::Engine(int msaa):
    window("Danzun", 500, 500, msaa),
    rc(this),
    audioDevice(NULL),
    audioContext(audioDevice),
    game(*this)
{
    setMaxFPS(120);
    window.setEventCallback(*this);
    s.open_libraries();
    audioContext.bind();

    // Create key mappings
    keyMappings["up"] = dan::keyt::UP;
    keyMappings["down"] = dan::keyt::DOWN;
    keyMappings["left"] = dan::keyt::LEFT;
    keyMappings["right"] = dan::keyt::RIGHT;
    keyMappings["esc"] = dan::keyt::ESCAPE;
    keyMappings["lshift"] = dan::keyt::LEFT_SHIFT;
    keyMappings["lalt"] = dan::keyt::LEFT_ALT;
    keyMappings["space"] = dan::keyt::SPACE;
    keyMappings["q"] = dan::keyt::Q;
    keyMappings["w"] = dan::keyt::W;
    keyMappings["e"] = dan::keyt::E;
    keyMappings["r"] = dan::keyt::R;
    keyMappings["t"] = dan::keyt::T;
    keyMappings["y"] = dan::keyt::Y;
    keyMappings["u"] = dan::keyt::U;
    keyMappings["i"] = dan::keyt::I;
    keyMappings["o"] = dan::keyt::O;
    keyMappings["p"] = dan::keyt::P;
    keyMappings["a"] = dan::keyt::A;
    keyMappings["s"] = dan::keyt::S;
    keyMappings["d"] = dan::keyt::D;
    keyMappings["f"] = dan::keyt::F;
    keyMappings["g"] = dan::keyt::G;
    keyMappings["h"] = dan::keyt::H;
    keyMappings["j"] = dan::keyt::J;
    keyMappings["k"] = dan::keyt::K;
    keyMappings["l"] = dan::keyt::L;
    keyMappings["z"] = dan::keyt::Z;
    keyMappings["x"] = dan::keyt::X;
    keyMappings["c"] = dan::keyt::C;
    keyMappings["v"] = dan::keyt::V;
    keyMappings["b"] = dan::keyt::B;
    keyMappings["n"] = dan::keyt::N;
    keyMappings["m"] = dan::keyt::M;
}


void dan::Engine::keyPressed(const event::KeyPress &e) {
}
void dan::Engine::mouseMoved(const event::MouseMove &e) {
}
void dan::Engine::mouseClicked(const event::MouseClick &e) {
}
void dan::Engine::mouseScrolled(const event::MouseScroll &e) {
}
void dan::Engine::charInput(const event::CharInput &e) {
}

dan::Engine::keyMappings_t &dan::Engine::getKeyMappings() {
    return keyMappings;
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

void dan::Engine::collectGarbage() {
	s.collect_garbage();
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

    // IMPORTANT: Set working directory to that of the init script
    // so that clients can use I/O sanely
    std::filesystem::current_path(filePath.parent_path());

    sol::function_result result = s.script_file(filePath.filename().string());

    if (!result.valid()) {
        sol::error e = result;
        err("Engine:open") << "Error while executing init script \"" << filePath << "\": " << e.what();
    }

    // Register all the classes and functions
    api::manifest::openAll(s);

    // Register singletons
    s["engine"] = api::Engine(*this);
    s["game"] = api::Game(game);
    s["player"] = api::Player(game.getPlayer());
    s["window"] = api::Window(window);

    cCall("init");

    window.setVisible(true);

    cCall("start");
}

void dan::Engine::start(const std::filesystem::path &filePath) {
    open(filePath);
    run();
}

// Static members

dan::Engine &dan::Engine::fromLua(sol::state_view lua) {
    // It's assumed that engine was not modified by client code
    // @TODO: Perhaps obfuscate the engine ref in case the client does something?
    api::Engine &engine = lua["engine"];
    return *engine.getHandle();
}
