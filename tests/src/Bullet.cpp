#include "Bullet.h"

#include <memory>

#include "../../src/math/Circle.h"

Bullet::Bullet(const dan::Sprite::texture_t &texture) {
    dan::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setWidth(30);
    sprite.setHeight(30);
    setSprite(sprite);
    std::shared_ptr<dan::Circle> hitbox = std::make_shared<dan::Circle>();
    hitbox->setRadius(30);
    setHitbox(hitbox);
    setViewHitbox(hitbox);
}
void Bullet::moveChild(child &c, dan::Game &g, float deltaTime) {
    c.position += c.velocity * deltaTime;
}
void Bullet::renderChild(child &c, dan::Game &g, dan::Context &ctx) {
    getSprite().setX(c.position.x);
    getSprite().setY(c.position.y);
    getSprite().render(ctx);
}
