#include "Enemy.h"

Enemy::Enemy(const dan::Sprite::texture_t &texture):
    dead(false),
    x(60),
    y(20)
{
    sprite.setTexture(texture);
    sprite.setWidth(50);
    sprite.setHeight(10);
    hitbox.setRadius(10);
}
const dan::Circle &Enemy::getHitbox() {
    hitbox.setX(x);
    hitbox.setY(y);
    return hitbox;
}
void Enemy::logic(dan::Game &g, float deltaTime) {
    y += deltaTime * 30;
    x += deltaTime * 10;
}
void Enemy::hit(dan::Game &g, dan::AbstractBulletType &culprate) {
    dead = true;
}
bool Enemy::shouldDelete() {
    return dead;
}
void Enemy::render(dan::Context &c) {
    if (!dead) {
        sprite.setX(x);
        sprite.setY(y);
        sprite.render(c);
    }
}
