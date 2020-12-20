#include "Engine.h"

#include "../lib/opengl.h"
#include "../lib/glfw.h"
#include "error.h"

#include "../api/Engine.h"
#include "../api/Game.h"
#include "../api/Shader.h"
#include "../api/Window.h"
#include "../api/Mesh.h"
#include "../api/Image.h"
#include "../api/Matrix.h"
#include "../api/Entity.h"
#include "../api/PatternVars.h"
#include "../api/RenderConfig.h"
#include "../api/Script.h"

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
dan::Data &dan::Engine::getData() {
    return data;
}
sol::state_view dan::Engine::getState() {
    return s;
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

        s.collect_garbage();

        sol::function_result mr = s["main"].call();
        if (!mr.valid()) {
            sol::error err = mr;
            std::cerr << "MAIN FUNCTION ERROR: " << err.what() << '\n';
        }
        game.render(rc);

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

void dan::Engine::cCall(const std::string &functionGlobalName) {
    sol::function func = s[functionGlobalName];
    if (func.get_type() == sol::type::function) {
        sol::function_result result = func.call();
        if (!result.valid()) {
            sol::error err = result;
            std::cerr << "FUNCTION ERROR: " << err.what() << std::endl;
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
    s.script_file(t.string());

    std::cout << "start open windows" << '\n';

    api::Engine::open(s);
    api::Shader::open(s);
    api::Mesh::open(s);
    api::Image::open(s);
    api::Game::open(s);
    api::Window::open(s);
    api::Matrix::open(s);
    api::PatternVars::open(s);
    api::Entity::open(s);
    api::RenderConfig::open(s);
    api::Script::open(s);

    s["engine"] = api::Engine(*this);
    s["game"] = api::Game(game);
    s["window"] = api::Window(window);

    std::cout << "libs done" << '\n';

    s.script_file(p.string());

    std::cout << "Setup done" << '\n';

    cCall("preInit");

    std::cout << "Pre done" << '\n';

    std::cout << "Engine opened" << '\n';

    window.setVisible(true);

    cCall("init");

    cCall("start");

    // Temp
    gameActive = true;
}

void dan::Engine::start(const std::filesystem::path &filePath) {
    open(filePath);
    run();
}

// Static members

dan::Engine &dan::Engine::fromLua(sol::state_view lua) {
    sol::table engine = lua["engine"];
    return *engine["getHandle"].call(engine).get<dan::Engine*>();
}
