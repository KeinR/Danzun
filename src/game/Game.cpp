#include "Game.h"

dan::Game::Game() {
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}

void dan::Game::addEntity(const entity_t &e) {
    entities.push_back(e);
}

int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}

std::vector<unsigned int> dan::Game::getLocalEntities(const hitbox_t &h) {
    // TEMP SOLUTION
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < entities.size(); i++) {
        result.push_back(i);
    }
    return result;
}
dan::Entity &dan::Game::getEntity(unsigned int index) {
    return *entities[index];
}

void dan::Game::pushBulletType(const bulletType_t &type) {
    bullets.push_back(type);
}
void dan::Game::logic(float deltaTime) {
    // ... update entity map ...

    for (bulletType_t &b : bullets) {
        b->logic(*this, deltaTime);
    }
}
void dan::Game::render(Context &c) {
    for (bulletType_t &b : bullets) {
        b->render(*this, c);
    }
}
