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

std::vector<std::pair<int,int>> dan::Game::testCollisions(const std::string &a, const std::string &b) {
    std::vector<std::pair<int,int>> result;
    groups[a].test(groups[b], result);
    return result;
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}


void dan::Game::addPattern(const std::string &name, const Pattern &p) {
    patterns[name] = p;
}
int dan::Game::newPatternInst(const std::string &name) {
    // patternInstancesId++;
    // patternInstances[patternInstancesId] = Pattern(*this, patterns[name]);
    // return patternInstancesId;
    DANZUN_ASSERT(false); // hold off on this for now; TEMP
}
dan::PatternInst &dan::Game::getPatternInst(int id) {
    return patternInstances[id];
}
void dan::Game::deletePatternInst(int id) {
    patternInstances.erase(id);
}


int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}


void dan::Game::logic(float deltaTime) {


    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }
}

void dan::Game::gc() {
    
}

void dan::Game::render(Context &c) {

}
