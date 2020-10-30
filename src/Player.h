#ifndef DANZUN_PLAYER_H_INCLUDED
#define DANZUN_PLAYER_H_INCLUDED

#include "Sprite.h"

namespace dan {
    class Game;
    class Context;
}

namespace dan {
    class Player {
        Sprite sprite;
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
        void setSprite(const Sprite &s);
        void render(Context &c);
    };
}

#endif
