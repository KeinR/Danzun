#include "Game.h"

#include <algorithm>
#include <iostream>

#include "../game/Game.h"
#include "../core/Context.h"

dan::api::Game::Game(::dan::Game &handle): handle(&handle) {
}

void dan::api::Game::setSize(int width, int height) {
    handle->setWidth(width);
    handle->setHeight(height);
}

void dan::api::Game::testCollisions(const std::string &groupA, const std::string &groupB) {
    for (std::pair<::dan::Game::entity_t, ::dan::Game::entity_t> &p : handle->testCollisions(groupA, groupB)) {
        // Each pair contains the members of one collision
        p.first->getHitCallback().call(::dan::api::Entity(p.first), ::dan::api::Entity(p.second));
        p.second->getHitCallback().call(::dan::api::Entity(p.second), ::dan::api::Entity(p.first));
    }
}

void dan::api::Game::setWidth(int w) {
    handle->setWidth(w);
}
void dan::api::Game::setHeight(int h) {
    handle->setHeight(h);
}
void dan::api::Game::setX(int x) {
    handle->setX(x);
}
void dan::api::Game::setY(int y) {
    handle->setY(y);
}
void dan::api::Game::setGCFactor(float f) {
    handle->setGCFactor(f);
}
void dan::api::Game::setGCConstant(float c) {
    handle->setGCConstant(c);
}
void dan::api::Game::setRunning(bool v) {
    handle->setRunning(v);
}
void dan::api::Game::setSpeed(float v) {
    handle->setSpeed(v);
}

void dan::api::Game::setGCTimeSeconds(float v) {
    handle->setGCTimeMilliseconds(static_cast<unsigned int>(std::ceil(v * 1000.0f)));
}
float dan::api::Game::getGCTimeSeconds() {
    return handle->getGCTimeMilliseconds() / 1000.0f;
}

int dan::api::Game::getWidth() {
    return handle->getWidth();
}
int dan::api::Game::getHeight() {
    return handle->getHeight();
}
int dan::api::Game::getX() {
    return handle->getX();
}
int dan::api::Game::getY() {
    return handle->getY();
}
float dan::api::Game::getGCFactor() {
    return handle->getGCFactor();
}
float dan::api::Game::getGCConstant() {
    return handle->getGCConstant();
}
bool dan::api::Game::isRunning() {
    return handle->isRunning();
}
float dan::api::Game::getSpeed() {
    return handle->getSpeed();
}


void dan::api::Game::clearGroups() {
    handle->clearGroups();
}
float dan::api::Game::getTime() {
    return handle->getClock().getTime();
}
float dan::api::Game::getDeltaTime() {
    return handle->getClock().getDeltaTime();
}

void dan::api::Game::render(sol::this_state l) {
    handle->render(Context::fromLua(l));
}

// Static members

void dan::api::Game::open(sol::state_view &lua) {
    sol::usertype<Game> type = lua.new_usertype<Game>("Game");

    type["testCollisions"] = &Game::testCollisions;
    type["getTime"] = &Game::getTime;
    type["getDeltaTime"] = &Game::getDeltaTime;
    type["setSize"] = &Game::setSize;
    type["clearGroups"] = &Game::clearGroups;

    type["gcConstant"] = sol::property(&Game::getGCConstant, &Game::setGCConstant);
    type["gcFactor"] = sol::property(&Game::getGCFactor, &Game::setGCFactor);
    type["width"] = sol::property(&Game::getWidth, &Game::setWidth);
    type["height"] = sol::property(&Game::getHeight, &Game::setHeight);
    type["gcInterval"] = sol::property(&Game::getGCTimeSeconds, &Game::setGCTimeSeconds);
    type["running"] = sol::property(&Game::isRunning, &Game::setRunning);
    type["speed"] = sol::property(&Game::getSpeed, &Game::setSpeed);
    type["x"] = sol::property(&Game::getX, &Game::setX);
    type["y"] = sol::property(&Game::setY, &Game::setY);
    type["render"] = &Game::render;

}
