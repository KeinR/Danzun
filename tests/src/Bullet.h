#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <memory>

#include "../../src/game/BulletType.h"
#include "../../src/AbsTexture.h"

class Bullet: public dan::BulletType {
protected:
    void move(child &c, dan::Game &g, float deltaTime) override;
    void render(child &c, dan::Game &g, dan::Context &ctx) override;
public:
    Bullet(const std::shared_ptr<dan::AbsTexture> &texture);
    long getDamage() override;
};

#endif
