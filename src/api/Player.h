#ifndef DANZUN_API_PLAYER_H_INCLUDED
#define DANZUN_API_PLAYER_H_INCLUDED

#include <sol/sol.hpp>

namespace dan {
    class Player;
}

namespace dan::api {
    class Player {
        ::dan::Player *handle;
    public:
        Player(::dan::Player &handle);

        void setX(float x);
        void setY(float y);
        void setWidth(float w);
        void setHeight(float h);
        void setSpeed(float v);

        float getX();
        float getY();

	void addUpKey(sol::this_state l, const std::string &name);
	void addDownKey(sol::this_state l, const std::string &name);
	void addLeftKey(sol::this_state l, const std::string &name);
	void addRightKey(sol::this_state l, const std::string &name);
	void clearKeys(sol::this_state l);

        static void open(sol::state_view lua);

    };
}

#endif
