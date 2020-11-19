#include "Player.h"

#include <cmath>
#include <iostream>

#include "Game.h"

dan::Player::Player(): speed(100), x(0), y(0) {
}
void dan::Player::move(Game &g, dir d, float deltaTime, bool combo) {
    float p = speed * deltaTime;
    if (combo) {
        // Angle is 45 degrees off of where it would be because it's
        // combo'd with another direction.
        // Multiply by sin(45)
        p *= std::sqrt(2.0f) / 2.0f;
    }
    switch (d) {
        case UP:
            y -= p;
            if (y < 0) {
                y = 0;
            }
            break;
        case DOWN:
            y += p;
            if (y + sprite.getHeight() > g.getHeight()) {
                y = g.getHeight() - sprite.getHeight();
            }
            break;
        case LEFT:
            x -= p;
            if (x < 0) {
                x = 0;
            }
            break;
        case RIGHT:
            x += p;
            if (x + sprite.getWidth() > g.getWidth()) {
                x = g.getWidth() - sprite.getWidth();
            }
            break;
    }
}

void dan::Player::setX(float nx) {
    x = nx;
}
void dan::Player::setY(float ny) {
    y = ny;
}

void dan::Player::setSpeed(float s) {
    speed = s;
}

void dan::Player::setSprite(const Sprite &s) {
    sprite = s;
}
void dan::Player::setHitbox(const Circle &h) {
    hitbox = h;
}

float dan::Player::getX() const {
    return x;
}
float dan::Player::getY() const {
    return y;
}

void dan::Player::render(Context &c) {
    sprite.setCenterX(x);
    sprite.setCenterY(y);
    sprite.render(c);
}

const dan::Circle &dan::Player::getHitbox() {
    hitbox.setX(x);
    hitbox.setY(y);
    return hitbox;
}
bool dan::Player::shouldDelete() {
    // Player always stays alive.
    // However, since it's always in the first index of game entities,
    // this function is never called...
    return false;
}
