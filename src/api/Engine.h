#ifndef DANZUN_API_ENGINE_H_INCLUDED
#define DANZUN_API_ENGINE_H_INCLUDED

#include <sol/forward.hpp>

namespace dan {
    class Engine;
}

namespace dan::api {
    class Engine {
        ::dan::Engine *handle;
    public:
        Engine(::dan::Engine &handle);

        ::dan::Engine *getHandle();
        void term(int status);

        static void open(sol::state_view &lua);
    };
}

#endif
