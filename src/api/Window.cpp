#include "Window.h"

#include <string>
#include <stdexcept>

#include <sol/sol.hpp>

#include "../win/Window.h"
#include "../core/util.h"

dan::api::Window::Window(::dan::Window &handle): handle(&handle) {
    keyMappings["up"] = dan::keyt::UP;
    keyMappings["down"] = dan::keyt::DOWN;
    keyMappings["left"] = dan::keyt::LEFT;
    keyMappings["right"] = dan::keyt::RIGHT;
    keyMappings["esc"] = dan::keyt::ESCAPE;
    keyMappings["z"] = dan::keyt::Z;
    keyMappings["x"] = dan::keyt::X;
}

void dan::api::Window::setTitle(const std::string &text) {
    handle->setTitle(text);
}
void dan::api::Window::setSize(int width, int height) {
    handle->setSize(width, height);
}
void dan::api::Window::setVisible(bool toggle) {
    handle->setVisible(toggle);
}
bool dan::api::Window::keyDown(const std::string &name) {
    keyMappings_t::iterator it = keyMappings.find(ut::lowercase(name));
    if (it != keyMappings.end()) {
        return handle->keyPressed(it->second);
    } else {
        throw std::invalid_argument("Key not found");
    }
}

// Static members

void dan::api::Window::open(sol::state_view lua) {
    sol::usertype<Window> type = lua.new_usertype<Window>("Window");

    type["setTitle"] = &Window::setTitle;
    type["setSize"] = &Window::setSize;
    type["setVisible"] = &Window::setVisible;
    type["keyDown"] = &Window::keyDown;

}
