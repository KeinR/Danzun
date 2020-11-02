#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "../../src/game/BulletType.h"

class Bullet: public dan::BulletType {
protected:
    void move(child &c, dan::Game &g, float deltaTime) override;
    void render(child &c, dan::Game &g, dan::Context &ctx) override;
public:
    Bullet(const dan::Sprite::texture_t &texture);
    long getDamage() override;
};

#endif
