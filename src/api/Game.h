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

        void regCircleCol(sol::table self, const std::string &groupName, float xCenter, float yCenter, float radius);
        void testCollisions(const std::string &groupA, const std::string &groupB);
        void resetGroups();
        float getTime();
        // void loadPatternsFromFile(const std::string &path);

        static void open(sol::state_view &lua);

    };
}

#endif