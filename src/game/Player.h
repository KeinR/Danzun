#ifndef DANZUN_PLAYER_H_INCLUDED
#define DANZUN_PLAYER_H_INCLUDED

#include "Entity.h"
#include "../Sprite.h"
#include "../math/Circle.h"

namespace dan {
    class Game;
    class Context;
}

namespace dan {
    class Player: public Entity {
        Sprite sprite;
        Circle hitbox;
        float speed;
        float x;
        float y;
    public:
        enum dir {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Player();

        void move(Game &g, dir d, float deltaTime, bool combo);
        void setX(float nx);
        void setY(float ny);
        void setSpeed(float s);
        void setSprite(const Sprite &s);
        void setHitbox(const Circle &h);

        float getX() const;
        float getY() const;

        void render(Context &c) override;
        // TODO: This should be pure virtual
        void logic(Game &g, float deltaTime) override;
        const Circle &getHitbox() override;
        void hit(Game &g, AbstractBulletType &culprate) override;
        bool shouldDelete() override;
    };
}

#endif