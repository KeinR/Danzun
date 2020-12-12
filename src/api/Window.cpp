#include "window.h"

#include <map>
#include <string>

#include <sol/sol.hpp>

#include "../../win/Window.h"
#include "../../win/enums.h"

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
void dan::api::Window::keyDown(const std::string &name) {
    for (char &c : name) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    return handle->keyPressed(keyMappings[name]);
}

// Static members

void dan::api::Window::open(sol::state_view &lua) {
    sol::usertype<Window> type = lua.new_usertype<Window>("Window");

    type["setTitle"] = &setTitle;
    type["setSize"] = &setSize;
    type["setVisible"] = &setVisible;
    type["keyDown"] = &keyDown;

}
