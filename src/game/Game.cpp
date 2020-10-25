#include "Game.h"

dan::Game::Game() {
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

void dan::Game::pushBulletType(const bulletType_t &type) {
    bullets.push_back(type);
}
void dan::Game::logic(float deltaTime) {
    for (bulletType_t &b : bullets) {
        b->logic(*this, deltaTime);
    }
}
void dan::Game::render(Context &c) {
    for (bulletType_t &b : bullets) {
        b->render(*this, c);
    }
}
