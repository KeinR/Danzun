#include "Script.h"

#include "../game/Game.h"
#include "../core/error.h"

dan::api::Script::Script(): stopOnFail(true), failed(true), done(true) {
}
dan::api::Script::Script(sol::this_state l, sol::function func, sol::variadic_args pargs):
    Script(l, func, std::vector<sol::object>(pargs.begin(), pargs.end()))
{
}
dan::api::Script::Script(sol::state_view lua, sol::function func, const std::vector<sol::object> &pargs):
    thread(sol::thread::create(lua)),
    routine(thread.state(), func),
    timeOfNextRun(0),
    stopOnFail(true),
    failed(false),
    done(false),
    args(pargs)
{
}
bool dan::api::Script::run(sol::this_state l) {
    if (!done && !(stopOnFail && failed)) {
        float time = Game::fromLua(l).getClock().getTime();
        if (time >= timeOfNextRun) {
            sol::function_result result = routine(sol::as_args(args));
            switch (result.status()) {
                case sol::call_status::ok:
                    // We're all done here, thread's ended
                    done = true;
                    break;
                case sol::call_status::yielded:
                    if (result.get_type() == sol::type::number) {
                        // Only advance time if actually yielded a number
                        timeOfNextRun = time + result.get<float>();
                    }
                    break;
                default:
                    failed = true;
                    sol::error serr = result;
                    err("api::Script::run", l) << "Callback failed: " << serr.what();
                    break;
            }
        }
    }
    return done;
}

bool dan::api::Script::isStopOnFail() {
    return stopOnFail;
}
bool dan::api::Script::isFailed() {
    return failed;
}

void dan::api::Script::setStopOnFail(bool v) {
    stopOnFail = v;
}
void dan::api::Script::setFailed(bool v) {
    failed = v;
}

void dan::api::Script::open(sol::state_view lua) {
    sol::usertype<Script> type = lua.new_usertype<Script>("Script",
        sol::constructors<Script(sol::this_state,sol::function,sol::variadic_args)>()
    );

    type["run"] = &Script::run;
    type["stopOnFail"] = sol::property(&Script::isStopOnFail, &Script::setStopOnFail);
    type["failed"] = sol::property(&Script::isFailed, &Script::setFailed);

}
