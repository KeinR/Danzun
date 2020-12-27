#ifndef DANZUN_API_SCRIPT_H_INCLUDED
#define DANZUN_API_SCRIPT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

namespace dan::api {
    class Script {
        sol::thread thread;
        sol::coroutine routine;
        float timeOfNextRun;
        bool stopOnFail;
        bool failed;
        bool done;
        std::vector<sol::object> args;
    public:
        // Default constructs all and sets `done` to true, so func calls do nothing...
        Script();
        Script(sol::this_state l, sol::function func, sol::variadic_args pargs);
        Script(sol::state_view lua, sol::function func, const std::vector<sol::object> &pargs);
        // Returns true if it's done
        bool run(sol::this_state l);

        bool isStopOnFail();
        bool isFailed();

        void setStopOnFail(bool v);
        void setFailed(bool v);

        static void open(sol::state_view lua);
    };
}

#endif
