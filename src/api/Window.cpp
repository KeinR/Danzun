#include "Window.h"

#include <map>
#include <string>

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
    return handle->keyPressed(keyMappings[ut::lowercase(name)]);
}

// Static members

void dan::api::Window::open(sol::state_view &lua) {
    sol::usertype<Window> type = lua.new_usertype<Window>("Window");

    type["setTitle"] = &Window::setTitle;
    type["setSize"] = &Window::setSize;
    type["setVisible"] = &Window::setVisible;
    type["keyDown"] = &Window::keyDown;

}
