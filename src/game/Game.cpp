#include "Game.h"

#include "../core/debug.h"

dan::Game::Game(Engine &e):
    engine(&e),
    // Clean up entities every ~5 seconds
    // (Not happening much, as there aren't many entities...)
    gcTimer(5000),
    autoGC(true)
{
}

dan::Engine &dan::Game::getEngine() const {
    return *engine;
}
dan::Group &dan::Game::getGroup(const std::string &name) {
    return groups[name];
}

void dan::Game::resetGroups() {
    for (auto &g : groups) {
        g.second.clear();
    }
}
void dan::Game::clearGroups() {
    groups.clear();
}

dan::Game::collisionResult_t dan::Game::testCollisions(const std::string &a, const std::string &b) {
    collisionResult_t result;
    groups[a].test(groups[b], result);
    return result;
}

dan::Game::entities_t::iterator dan::Game::deleteEntity(const entities_t::iterator &it) {
    Entity *ptr = &(*it);
    // Will only be in one collision group, however arbitrary normal groups
    for (auto &p : groups) {
        if (p.second.erase(ptr)) {
            break;
        }
    }
    for (auto &p : collisionGroups) {
        p.second.erase(ptr);
    }
    removeRenderable(ptr);
    return entities.erase(it);
}

dan::Entity &dan::Game::addEntity(sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC) {
    entities.emplace_back(*this, hitCallback, disp, equation, x, y, width, height, autoGC);
    return entities.back();
}

void dan::Game::submitRenderable(Renderable &rend) {
    renderQueue[priority] = &rend;
}
void dan::Game::removeRenderable(Renderable *rend) {
    for (renderQueue_t it = renderQueue.begin(); it != renderQueue.end();) {
        if (it->second == rend) {
            it = renderQueue.erase(it);
        } else {
            ++it;
        }
    }
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}



int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}


void dan::Game::logic(float deltaTime) {
    clock.pushDeltaTime(deltaTime);

    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }

    for (Entity &e : entities) {
        e.run();
    }

    for (auto &p : groups) {
        p.second.update();
    }
}

void dan::Game::gc() {
    for (Entity &e : entities) {
        // TODO
    }
}

void dan::Game::render(Context &c) {
    for (auto &p : renderQueue) {
        p.second.render(c);
    }
}
