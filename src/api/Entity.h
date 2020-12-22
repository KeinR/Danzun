#ifndef DAN_API_ENTITY_H_INCLUDED
#define DAN_API_ENTITY_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

namespace dan {
    class Entity;
}

namespace dan::api {
    class Entity {
    public:
        typedef std::shared_ptr<::dan::Entity> handle_t;
    private:
        handle_t handle;
    public:
        Entity(const handle_t &handle);

        handle_t getHandle();

        void setScript(sol::this_state l, sol::function func, sol::variadic_args pargs);

        int getX();
        int getY();

        static void open(sol::state_view &lua);
    };
}

#endif
