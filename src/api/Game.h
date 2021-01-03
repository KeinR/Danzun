#ifndef DANZUN_API_GAME_H_INCLUDED
#define DANZUN_API_GAME_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan {
    class Game;
}

namespace dan::api {
    class Game {
        ::dan::Game *handle;
    public:
        Game(::dan::Game &handle);

        void setSize(int width, int height);

        void testCollisions(const std::string &groupA, const std::string &groupB);
        void resetGroups();
        float getTime();
        float getDeltaTime();

        void setWidth(int w);
        void setHeight(int h);
        void setGCFactor(float f);
        void setGCConstant(float c);
        void setRunning(bool v);
        void setSpeed(float v);

        void setGCTimeSeconds(float v);
        float getGCTimeSeconds();

        int getWidth();
        int getHeight();
        float getGCFactor();
        float getGCConstant();
        bool isRunning();
        float getSpeed();

        static void open(sol::state_view &lua);

    };
}

#endif
