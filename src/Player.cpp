#include "Player.h"

dan::Player::Player(): speed(1) {
}
void dan::Player::setSprite(const Sprite &s) {
    sprite = s;
}
