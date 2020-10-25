#ifndef DANZUN_PLAYER_H_INCLUDED
#define DANZUN_PLAYER_H_INCLUDED

#include "Sprite.h"

namespace dan {
    class Player {
        Sprite sprite;
        float speed;
    public:
        Player();
        void setSprite(const Sprite &s);
    };
}

#endif
