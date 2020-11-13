#include "BasicEnemy.h"

#include <cmath>

#include "AbsBulletType.h"

dan::BasicEnemy::BasicEnemy(): health(0) {
}
dan::BasicEnemy::BasicEnemy(long health, const Sprite &sprite): BasicEnemy() {
    setHealth(health);
    setSprite(sprite);
}
dan::BasicEnemy::~BasicEnemy() {
}
void dan::BasicEnemy::setHealth(long health) {
    this->health = health;
}
void dan::BasicEnemy::setSprite(const Sprite &sprite) {
    this->sprite = sprite;
    hitbox.setRadius(
        std::min(sprite.getWidth(), sprite.getHeight()) / 2.0f
    );
}
long dan::BasicEnemy::getHealth() const {
    return health;
}
dan::Sprite &dan::BasicEnemy::getSprite() {
    return sprite;
}

void dan::BasicEnemy::setX(int x) {
    hitbox.setX(x);
}
void dan::BasicEnemy::setY(int y) {
    hitbox.setY(y);
}
int dan::BasicEnemy::getX() const {
    return hitbox.getX();
}
int dan::BasicEnemy::getY() const {
    return hitbox.getY();
}

const dan::Circle &dan::BasicEnemy::getHitbox() {
    return hitbox;
}
void dan::BasicEnemy::logic(Game &g, float deltaTime) {
    // Do nothing...
}
void dan::BasicEnemy::hit(Game &g, AbsBulletType &culprate) {
    long newHealth = getHealth() - culprate.getDamage();
    setHealth(std::max(newHealth, 0l));
}
bool dan::BasicEnemy::shouldDelete() {
    return getHealth() <= 0;
}
void dan::BasicEnemy::render(Context &c) {
    sprite.setX(hitbox.getMinX());
    sprite.setY(hitbox.getMinY());
    sprite.render(c);
}
