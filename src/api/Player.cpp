#include "Player.h"

#include "../game/Player.h"

dan::api::Player::Player(::dan::Player &handle): handle(&handle) {
}

void dan::api::Player::setX(float x) {
    handle->setX(x);
}
void dan::api::Player::setY(float y) {
    handle->setY(y);
}
void dan::api::Player::setWidth(float w) {
    handle->setWidth(w);
}
void dan::api::Player::setHeight(float h) {
    handle->setHeight(h);
}
void dan::api::Player::setSpeed(float v) {
    handle->setSpeed(v);
}

float dan::api::Player::getX() {
    return handle->getX();
}
float dan::api::Player::getY() {
    return handle->getY();
}

void dan::api::Player::open(sol::state_view lua) {
    sol::usertype<Player> type = lua.new_usertype<Player>("Player");

    type["width"] = sol::property(&Player::setWidth);
    type["height"] = sol::property(&Player::setHeight);
    type["speed"] = sol::property(&Player::setSpeed);
    type["x"] = sol::property(&Player::getX, &Player::setX);
    type["y"] = sol::property(&Player::getY, &Player::setY);
}
