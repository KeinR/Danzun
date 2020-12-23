#ifndef DANZUN_API_GAME_H_INCLUDED
#define DANZUN_API_GAME_H_INCLUDED

#include <string>
#include <vector>
#include <utility>
#include <memory>

#include <sol/sol.hpp>

#include "Entity.h"
#include "../game/Entity.h"
#include "Effect.h"
#include "RenderConfig.h"

namespace dan {
    class Game;
}

namespace dan::api {
    class Game {
        ::dan::Game *handle;
    public:
        Game(::dan::Game &handle);

        void setSize(int width, int height);

        // void regCircleCol(sol::table self, const std::string &groupName, float xCenter, float yCenter, float radius);
        void testCollisions(const std::string &groupA, const std::string &groupB);
        void resetGroups();
        float getTime();
        float getDeltaTime();

        static void open(sol::state_view &lua);

    };
}

#endif
