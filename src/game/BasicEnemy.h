#ifndef DANZUN_BASICENEMY_H_INCLUDED
#define DANZUN_BASICENEMY_H_INCLUDED

#include "../sprite/Sprite.h"
#include "../math/Circle.h"

#include "Entity.h"

namespace dan {
    class BasicEnemy: public Entity {
        long health;
        Sprite sprite;
        Circle hitbox;
    public:
        BasicEnemy();
        BasicEnemy(long health, const Sprite &sprite);
        virtual ~BasicEnemy();

        void setHealth(long health);
        void setSprite(const Sprite &sprite);
        long getHealth() const;
        Sprite &getSprite();

        void setX(int x);
        void setY(int y);
        int getX() const;
        int getY() const;

        const Circle &getHitbox() override;
        virtual void logic(Game &g, float deltaTime) override;
        virtual void hit(Game &g, AbsBulletType &culprate) override;
        virtual bool shouldDelete() override;
        virtual void render(Context &c) override;
    };
}

#endif
