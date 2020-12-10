#include "window.h"

#include <map>
#include <string>

#include "../../win/Window.h"
#include "../../win/enums.h"

dan::api::Window(::dan::Window &handle): handle(&handle) {
    keyMappings["up"] = dan::keyt::UP;
    keyMappings["down"] = dan::keyt::DOWN;
    keyMappings["left"] = dan::keyt::LEFT;
    keyMappings["right"] = dan::keyt::RIGHT;
    keyMappings["esc"] = dan::keyt::ESCAPE;
    keyMappings["z"] = dan::keyt::Z;
    keyMappings["x"] = dan::keyt::X;
}

void dan::api::setTitle(const std::string &text) {
    handle->setTitle(text);
}
void dan::api::setSize(int width, int height) {
    handle->setSize(width, height);
}
void dan::api::setVisible(bool toggle) {
    handle->setVisible(toggle);
}
void dan::api::keyDown(const std::string &name) {
    for (char &c : name) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    return handle->keyPressed(keyMappings[name]);
}

// Static members

void dan::api::open(sol::state_view &lua) {
    
}
