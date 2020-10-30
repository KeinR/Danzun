#include "Player.h"

#include <cmath>

#include "game/Game.h"

dan::Player::Player(): speed(1), x(0), y(0) {
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
                x = sprite.getWidth() - sprite.getWidth();
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

void dan::Player::setSprite(const Sprite &s) {
    sprite = s;
}
void dan::Player::render(Context &c) {
    sprite.setX(x);
    sprite.setY(y);
    sprite.render(c);
}
