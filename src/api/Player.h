#ifndef DANZUN_API_PLAYER_H_INCLUDED
#define DANZUN_API_PLAYER_H_INCLUDED

#include <sol/sol.hpp>

namespace dan {
    class Player;
}

namespace dan::api {
    /**
     * Interface to the player class (singleton)
     * */
    class Player {
        //. The handle
        ::dan::Player *handle;
    public:
        /**
         * Construct a new interface
         * \param handle The player
         * */
        Player(::dan::Player &handle);

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

        /// @{
        /**
         * Get properties of the player
         * */

        float getX();
        float getY();

        /// @}


        /// @{
        /**
         * Maps a key's name to its enum value and adds as a movement key
         * \param l The current state
         * \param name The name of the key
         * */
	void addUpKey(sol::this_state l, const std::string &name);
	void addDownKey(sol::this_state l, const std::string &name);
	void addLeftKey(sol::this_state l, const std::string &name);
	void addRightKey(sol::this_state l, const std::string &name);
        /// @}
        /**
         * Deletes all added keys
         * \param l The current state
         * */
	void clearKeys(sol::this_state l);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view lua);

    };
}

#endif
