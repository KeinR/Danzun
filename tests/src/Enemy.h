#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "../../src/game/Entity.h"
#include "../../src/Sprite.h"
#include "../../src/math/Circle.h"

class Enemy: public dan::Entity {
    dan::Sprite sprite;
    dan::Circle hitbox;
    bool dead;
    float x;
    float y;
public:
    Enemy(const dan::Sprite::texture_t &texture);
    const dan::Circle &getHitbox() override;
    void logic(dan::Game &g, float deltaTime) override;
    void hit(dan::Game &g, dan::AbstractBulletType &culprate) override;
    bool shouldDelete() override;
    void render(dan::Context &c) override;
};

#endif
