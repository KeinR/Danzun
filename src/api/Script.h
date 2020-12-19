#ifndef DAN_API_SCRIPT_H_INCLUDED
#define DAN_API_SCRIPT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

namespace dan::api {
    class Script {
        sol::thread thread;
        sol::coroutine routine;
        float timeOfNextRun;
        bool done;
        std::vector<sol::object> args;
    public:
        Script(sol::this_state, sol::function func, sol::variadic_args pargs);
        // Returns true if it's done
        bool run(sol::this_state l);

        static void open(sol::state_view lua);
    };
}

#endif
