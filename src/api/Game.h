#ifndef DANZUN_API_GAME_H_INCLUDED
#define DANZUN_API_GAME_H_INCLUDED

#include <string>
#include <vector>
#include <utility>

#include <sol/sol.hpp>

#include "Entity.h"

namespace dan {
    class Game;
}

namespace dan::api {
    class Game {
        ::dan::Game *handle;
    public:
        Game(::dan::Game &handle);

        // void regCircleCol(sol::table self, const std::string &groupName, float xCenter, float yCenter, float radius);
        void testCollisions(const std::string &groupA, const std::string &groupB);
        void resetGroups();
        float getTime();
        float getDeltaTime();
        // void loadPatternsFromFile(const std::string &path);

        Entity spawnEntityFull(
            sol::function hitCallback, sol::userdata disp, const std::string &equation,
            sol::table vars, sol::table constants,
            float x, float y, float width, float height, bool autoGC,
            const std::string &group, int renderPriority,
            sol::object points // If not nil, assumes that hitbox is polygon. Else, circle.
        );

        static void open(sol::state_view &lua);

    };
}

#endif
