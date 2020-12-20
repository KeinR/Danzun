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

float dan::api::Player::getX() {
    return handle->getX();
}
float dan::api::Player::getY() {
    return handle->getY();
}

void dan::api::Player::open(sol::state_view lua) {
    sol::usertype<Player> type = lua.new_usertype<Player>("Player");

    type["setX"] = &Player::setX;
    type["setY"] = &Player::setY;
    type["getX"] = &Player::getX;
    type["getY"] = &Player::getY;
}
