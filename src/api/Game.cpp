#include "Game.h"

#include <stdexcept>

#include "../game/Game.h"
#include "PatternVars.h"
#include "../core/debug.h"


dan::api::Game::Game(::dan::Game &handle): handle(&handle) {
}

void dan::api::Game::setSize(int width, int height) {
    handle->setWidth(width);
    handle->setHeight(height);
}

void dan::api::Game::testCollisions(const std::string &groupA, const std::string &groupB) {
    for (std::pair<::dan::Game::entity_t, ::dan::Game::entity_t> &p : handle->testCollisions(groupA, groupB)) {
        p.first->getHitCallback().call(::dan::api::Entity(p.first), ::dan::api::Entity(p.second));
        p.second->getHitCallback().call(::dan::api::Entity(p.second), ::dan::api::Entity(p.first));
    }
}

void dan::api::Game::resetGroups() {
    handle->resetGroups();
}
float dan::api::Game::getTime() {
    return handle->getClock().getTime();
}
float dan::api::Game::getDeltaTime() {
    return handle->getClock().getDeltaTime();
}

// Static members

void dan::api::Game::open(sol::state_view &lua) {
    sol::usertype<Game> type = lua.new_usertype<Game>("Game");

    type["testCollisions"] = &Game::testCollisions;
    type["resetGroups"] = &Game::resetGroups;
    type["getTime"] = &Game::getTime;
    type["getDeltaTime"] = &Game::getDeltaTime;
    type["setSize"] = &Game::setSize;

}
