#include "Player.h"

#include "../game/Player.h"
#include "../game/Game.h"
#include "../core/Engine.h"

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


void dan::api::Player::addUpKey(sol::this_state l, const std::string &name) {
    Game::fromLua(l).getUpKeys().push_back(Engine::fromLua(l).getKeyMappings()[name]);
}

void dan::api::Player::addDownKey(sol::this_state l, const std::string &name) {
    Game::fromLua(l).getDownKeys().push_back(Engine::fromLua(l).getKeyMappings()[name]);
}

void dan::api::Player::addLeftKey(sol::this_state l, const std::string &name) {
    Game::fromLua(l).getLeftKeys().push_back(Engine::fromLua(l).getKeyMappings()[name]);
}

void dan::api::Player::addRightKey(sol::this_state l, const std::string &name) {
    Game::fromLua(l).getRightKeys().push_back(Engine::fromLua(l).getKeyMappings()[name]);
}

void dan::api::Player::clearKeys(sol::this_state l) {
    Game::fromLua(l).getUpKeys().clear();
    Game::fromLua(l).getDownKeys().clear();
    Game::fromLua(l).getLeftKeys().clear();
    Game::fromLua(l).getRightKeys().clear();
}

void dan::api::Player::open(sol::state_view lua) {
    sol::usertype<Player> type = lua.new_usertype<Player>("Player");

    type["width"] = sol::property(&Player::setWidth);
    type["height"] = sol::property(&Player::setHeight);
    type["speed"] = sol::property(&Player::setSpeed);
    type["x"] = sol::property(&Player::getX, &Player::setX);
    type["y"] = sol::property(&Player::getY, &Player::setY);

    type["addUpKey"] = &Player::addUpKey;
    type["addDownKey"] = &Player::addDownKey;
    type["addLeftKey"] = &Player::addLeftKey;
    type["addRightKey"] = &Player::addRightKey;
    type["clearKeys"] = &Player::clearKeys;
}
