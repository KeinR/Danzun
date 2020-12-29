#include "Window.h"

#include <mutex>

#include "../core/error.h"
#include "../core/util.h"
#include "../core/pmeta.h"
#include "../win/Window.h"

dan::api::Window::Window(::dan::Window &handle): handle(&handle) {
    keyMappings["up"] = dan::keyt::UP;
    keyMappings["down"] = dan::keyt::DOWN;
    keyMappings["left"] = dan::keyt::LEFT;
    keyMappings["right"] = dan::keyt::RIGHT;
    keyMappings["esc"] = dan::keyt::ESCAPE;
    keyMappings["z"] = dan::keyt::Z;
    keyMappings["x"] = dan::keyt::X;
}

bool dan::api::Window::checkMainThread(sol::this_state l, const char *trace) {
    if (!pmeta::onMainThread()) {
        err(trace, l) << "Can only modify window from main thread";
        return false;
    } else {
        return true;
    }
}

void dan::api::Window::setTitle(sol::this_state l, const std::string &text) {
    if (checkMainThread(l, "api::Window::setTitle")) {
        handle->setTitle(text);
    }
}
void dan::api::Window::setSize(sol::this_state l, int width, int height) {
    if (checkMainThread(l, "api::Window::setSize")) {
        handle->setSize(width, height);
    }
}
void dan::api::Window::setVisible(sol::this_state l, bool toggle) {
    if (checkMainThread(l, "api::Window::setVisible")) {
        handle->setVisible(toggle);
    }
}
bool dan::api::Window::keyDown(sol::this_state l, const std::string &name) {
    static const char *const funcSig = "api::Window::keyDown";
    if (checkMainThread(l, funcSig)) {
        keyMappings_t::iterator it = keyMappings.find(ut::lowercase(name));
        if (it != keyMappings.end()) {
            return handle->keyPressed(it->second);
        } else {
            err(funcSig, l) << "No key mapping for \"" << name << "\"";
        }
    }
    return false;
}

// Static members

void dan::api::Window::open(sol::state_view lua) {
    sol::usertype<Window> type = lua.new_usertype<Window>("Window");

    type["setTitle"] = &Window::setTitle;
    type["setSize"] = &Window::setSize;
    type["setVisible"] = &Window::setVisible;
    type["keyDown"] = &Window::keyDown;

}
