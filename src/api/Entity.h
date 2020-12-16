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
        // Superfluous calls are ignored 
        void addVars(sol::userdata patternVars);

        static void open(sol::state_view &lua);
    };
}

#endif
