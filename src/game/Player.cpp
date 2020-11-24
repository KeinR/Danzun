#include "Player.h"

#include <cmath>
#include <iostream>

#include "Game.h"

dan::Player::Player(): speed(100), pos(0, 0) {
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
            pos.y -= p;
            if (pos.y < 0) {
                pos.y = 0;
            }
            break;
        case DOWN:
            pos.y += p;
            if (pos.y + sprite.getHeight() > g.getHeight()) {
                pos.y = g.getHeight() - sprite.getHeight();
            }
            break;
        case LEFT:
            pos.x -= p;
            if (pos.x < 0) {
                pos.x = 0;
            }
            break;
        case RIGHT:
            pos.x += p;
            if (pos.x + sprite.getWidth() > g.getWidth()) {
                pos.x = g.getWidth() - sprite.getWidth();
            }
            break;
    }
}

void dan::Player::setPos(const glm::vec2 &npos) {
    pos = npos;
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

const glm::vec2 &dan::Player::getPos() const {
    return pos;
}

void dan::Player::render(Context &c) {
    sprite.setCenterX(pos.x);
    sprite.setCenterY(pos.y);
    sprite.render(c);
}

const dan::Circle &dan::Player::getHitbox() {
    hitbox.setX(pos.x);
    hitbox.setY(pos.y);
    return hitbox;
}
bool dan::Player::shouldDelete() {
    // Player always stays alive.
    // However, since it's always in the first index of game entities,
    // this function is never called...
    return false;
}
