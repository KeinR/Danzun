#include "Bullet.h"


#include "../../src/math/Circle.h"
#include "../../src/sprite/ImgDisp.h"

Bullet::Bullet(const std::shared_ptr<dan::AbsTexture> &texture) {
    dan::Sprite sprite;
    sprite.setConf(std::make_shared<dan::ImgDisp>(texture));
    sprite.setWidth(30);
    sprite.setHeight(30);
    setSprite(sprite);
    std::shared_ptr<dan::Circle> hitbox = std::make_shared<dan::Circle>();
    hitbox->setRadius(15);
    setHitbox(hitbox);
    setViewHitbox(hitbox);
}
void Bullet::move(child &c, dan::Game &g, float deltaTime) {
    c.position += c.velocity * deltaTime;
}
void Bullet::render(child &c, dan::Game &g, dan::Context &ctx) {
    getSprite().setCenterX(c.position.x);
    getSprite().setCenterY(c.position.y);
    getSprite().render(ctx);
}

long Bullet::getDamage() {
    return 1;
}
