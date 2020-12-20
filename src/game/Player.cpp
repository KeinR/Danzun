#include "Player.h"

#include <cmath>

dan::Player::Player(): pos{0, 0}, speed(5) {
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

void dan::Player::move(const dir &d, float deltaTime) {
    float m = speed * deltaTime;
    // If diagonal
    if ((d.up ^ d.down) && (d.left ^ d.right)) {
        m *= std::sqrt(2) / 2;
    }
    if (d.up) {
        pos[1] -= m;
    }
    if (d.down) {
        pos[1] += m;
    }
    if (d.left) {
        pos[0] -= m;
    }
    if (d.right) {
        pos[0] += m;
    }
}
