#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <memory>

#include "../../src/game/Entity.h"
#include "../../src/sprite/Sprite.h"
#include "../../src/sprite/AbsTexture.h"
#include "../../src/math/Circle.h"

class Enemy: public dan::Entity {
    dan::Sprite sprite;
    dan::Circle hitbox;
    float x;
    float y;
    long health;
public:
    Enemy(const std::shared_ptr<dan::AbsTexture> &texture);
    const dan::Circle &getHitbox() override;
    void logic(dan::Game &g, float deltaTime) override;
    void hit(dan::Game &g, dan::AbsBulletType &culprate) override;
    bool shouldDelete() override;
    void render(dan::Context &c) override;
};

#endif
