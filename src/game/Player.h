#ifndef DAN_PLAYER_H_INCLUDED
#define DAN_PLAYER_H_INCLUDED

#include <array>

namespace dan {
    class Game;
}

namespace dan {
    class Player {
        std::array<float, 2> pos;
        float speed;
        // Only set externally and used in calculations.
        float semiMinor; // y
        float semiMajor; // x
    public:
        struct dir {
            bool up;
            bool down;
            bool left;
            bool right;
        };

        Player();
        float &getXRef();
        float &getYRef();
        std::array<float, 2> &getPos();
        float getX() const;
        float getY() const;

        void setX(float x);
        void setY(float y);
        void setWidth(float w);
        void setHeight(float h);

        void move(Game &g, const dir &d, float deltaTime);
    };
}

#endif
