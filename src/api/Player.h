#ifndef DAN_API_PLAYER_H_INCLUDED
#define DAN_API_PLAYER_H_INCLUDED

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

        float getX();
        float getY();

        static void open(sol::state_view lua);

    };
}

#endif
