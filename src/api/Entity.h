#ifndef DAN_API_ENTITY_H_INCLUDED
#define DAN_API_ENTITY_H_INCLUDED

#include <sol/sol.hpp>

namespace dan {
    class Entity;
}

namespace dan::api {
    class Entity {
        ::dan::Entity *handle;
    public:
        Entity(::dan::Entity &handle);

        ::dan::Entity &getHandle();

        void setScript(sol::this_state l, sol::function func, sol::variadic_args pargs);

        int getX();
        int getY();

        static void open(sol::state_view &lua);
    };
}

#endif
