#ifndef DANZUN_PLAYER_H_INCLUDED
#define DANZUN_PLAYER_H_INCLUDED

#include <glm/glm.hpp>

#include "Entity.h"

#include "../sprite/Sprite.h"
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
        glm::vec2 pos;
    public:
        enum dir {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };

        Player();

        void move(Game &g, dir d, float deltaTime, bool combo);
        void setPos(const glm::vec2 &npos);
        void setSpeed(float s);
        void setSprite(const Sprite &s);
        void setHitbox(const Circle &h);

        const glm::vec2 &getPos() const;

        void render(Context &c) override;
        // TODO: This should be pure virtual
        virtual void logic(Game &g, float deltaTime) override = 0;
        const Circle &getHitbox() override;
        virtual void hit(Game &g, AbsBulletType &culprate) override = 0;
        bool shouldDelete() override;
    };
}

#endif
