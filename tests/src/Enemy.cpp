#include "Enemy.h"

#include <iostream>

#include "../../src/game/AbstractBulletType.h"

Enemy::Enemy(const dan::Sprite::texture_t &texture):
    x(100),
    y(200),
    health(100)
{
    sprite.setTexture(texture);
    sprite.setWidth(50);
    sprite.setHeight(50);
    hitbox.setRadius(25);
}
const dan::Circle &Enemy::getHitbox() {
    hitbox.setX(x);
    hitbox.setY(y);
    return hitbox;
}
void Enemy::logic(dan::Game &g, float deltaTime) {
    // y += deltaTime * 3;
    // x += deltaTime * 2;
}
void Enemy::hit(dan::Game &g, dan::AbstractBulletType &culprate) {
    health -= culprate.getDamage();
    std::cout << "Health reduced to " << health << '\n';
}
bool Enemy::shouldDelete() {
    // return health < 0;
    return false;
}
void Enemy::render(dan::Context &c) {
    sprite.setCenterX(x);
    sprite.setCenterY(y);
    sprite.render(c);
}
