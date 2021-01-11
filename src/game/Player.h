#ifndef DANZUN_PLAYER_H_INCLUDED
#define DANZUN_PLAYER_H_INCLUDED

#include <array>

namespace dan {
    class Game;
}

namespace dan {
    /**
     * Intelligently keeps track of the player's position
     * */
    class Player {
        /// The player's x/y position
        std::array<float, 2> pos;
        /// The speed of the player in units/second
        float speed;
        /// The vertical radius (y)
        float semiMinor;
        /// The horizontal radius (x)
        float semiMajor;
    public:
        /**
         * Different directions that the player is moving
         * */
        struct dir {
            bool up;
            bool down;
            bool left;
            bool right;
        };

        /**
         * Defaults to certain values
         * */
        Player();

        /**
         * \return Reference to the player's x
         * */
        float &getXRef();
        /**
         * \return Reference to the player's y
         * */
        float &getYRef();
        /**
         * \return the player's position
         * */
        std::array<float, 2> &getPos();
        /**
         * \return The player's x coordinate
         * */
        float getX() const;
        /**
         * \return The player's y coordinate
         * */
        float getY() const;

        /// @{
        /**
         * Set properties of the player
         * */
        void setX(float x);
        void setY(float y);
        void setWidth(float w);
        void setHeight(float h);
        void setSpeed(float v);
        /// @}

        /**
         * Perform movement calcualtions given directions,
         * time, and the game.
         * Takes into account the size of the player and the boarder
         * (game size)
         * \param g The game singleton
         * \param d The direction of movement
         * \param deltaTime The time elapsed while moving
         * */
        void move(Game &g, const dir &d, float deltaTime);
    };
}

#endif
