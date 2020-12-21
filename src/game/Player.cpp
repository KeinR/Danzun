#include "Player.h"

#include <cmath>

#include "Game.h"

dan::Player::Player(): pos{0, 0}, speed(30), semiMinor(10), semiMajor(10) {
}
float &dan::Player::getXRef() {
    return pos[0];
}
float &dan::Player::getYRef() {
    return pos[1];
}
std::array<float, 2> &dan::Player::getPos() {
    return pos;
}
float dan::Player::getX() const {
    return pos[0];
}
float dan::Player::getY() const {
    return pos[1];
}

void dan::Player::setX(float x) {
    pos[0] = x;
}
void dan::Player::setY(float y) {
    pos[1] = y;
}
void dan::Player::setWidth(float w) {
    semiMajor = w / 2.0f;
}
void dan::Player::setHeight(float h) {
    semiMinor = h / 2.0f;
}

void dan::Player::move(Game &g, const dir &d, float deltaTime) {
    float m = speed * deltaTime;
    // If diagonal
    if ((d.up ^ d.down) && (d.left ^ d.right)) {
        m *= std::sqrt(2) / 2;
    }
    float &x = pos[0];
    float &y = pos[1];
    if (d.up) {
        y -= m;
        if (y - semiMinor < 0) {
            y = semiMinor;
        }
    }
    if (d.down) {
        y += m;
        if (y + semiMinor > g.getHeight()) {
            y = g.getHeight() - semiMinor;
        }
    }
    if (d.left) {
        x -= m;
        if (x - semiMajor < 0) {
            x = semiMajor;
        }
    }
    if (d.right) {
        x += m;
        if (x + semiMajor > g.getWidth()) {
            x = g.getWidth() - semiMajor;
        }
    }
}
