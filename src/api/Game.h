#ifndef DANZUN_API_GAME_H_INCLUDED
#define DANZUN_API_GAME_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan {
    class Game;
}

namespace dan::api {
    /**
     * Interface to the master game class.
     * */
    class Game {
        /// Handle to the master game class
        ::dan::Game *handle;
    public:
        /**
         * Construct with the master game class.
         * */
        Game(::dan::Game &handle);

        /**
         * Sets the size of the game area.
         * This determines where the player is allowed to go,
         * as well as what entities should be deleted by autoGC.
         * \param width The width
         * \param height The height
         * \see setWidth
         * \see setHeight
         * */
        void setSize(int width, int height);

        /**
         * Pits the hitboxes in two different gorups against each-other.
         * For each collision, the respective callbacks are called.
         * The order of the groups doesn't particularly matter.
         * \param groupA The first group
         * \param groupB The second group
         * */
        void testCollisions(const std::string &groupA, const std::string &groupB);
        /**
         * Deletes all hitboxes and their respective groups.
         * */
        void clearGroups();
        /**
         * Gets the current game time
         * \return The time in seconds
         * */
        float getTime();
        /**
         * Gets the change in game time from the last frame
         * \return The time, in seconds
         * */
        float getDeltaTime();

        /**
         * Set the width
         * \param w The width
         * */
        void setWidth(int w);
        /**
         * Set the height
         * \param The height
         * */
        void setHeight(int h);
        void setX(int x);
        void setY(int y);
        /** set the gcFactor
         * \param f New factor
         * */
        void setGCFactor(float f);
        /**
         * Set the gcConstant
         * \param c The new constant
         * */
        void setGCConstant(float c);
        /**
         * Set if the game is running.
         * This determines if logic (like entity expressions) will be processed,
         * as well as manual garbage collection.
         * */
        void setRunning(bool v);
        /**
         * Set the game speed
         * \param v The new multiplyer
         * */
        void setSpeed(float v);

        /**
         * Set the gc time
         * \param v The time in seconds
         * */
        void setGCTimeSeconds(float v);
        /**
         * Get the gc tiem
         * \return The time, in seconds
         * */
        float getGCTimeSeconds();

        /**
         * \return The game width
         * */
        int getWidth();
        /**
         * \return The game height
         * */
        int getHeight();
        int getX();
        int getY();
        /** 
         * \return The gc factor
         * */
        float getGCFactor();
        /**
         * \return THe gc constant
         * */
        float getGCConstant();
        /**
         * \return true if the game is running
         * */
        bool isRunning();
        /**
         * \return the game speed
         * */
        float getSpeed();

        void render(sol::this_state l);

        /**
         * Registers this class with the given state
         * \param lua The current state
         * */
        static void open(sol::state_view &lua);

    };
}

#endif
