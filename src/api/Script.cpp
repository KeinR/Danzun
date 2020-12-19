#include "Script.h"

#include "../game/Game.h"

dan::api::Script::Script(sol::this_state l, sol::function func, sol::variadic_args pargs):
    thread(sol::thread::create(l)),
    routine(thread.state(), func),
    timeOfNextRun(0),
    done(false),
    args(pargs.begin(), pargs.end())
{
}
bool dan::api::Script::run(sol::this_state l) {
    if (!done) {
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
                    // There was an error :(
                    // Well, don't try that again...
                    sol::error err = result;
                    std::cerr << "SCRIPT ERROR: " << err.what() << '\n';
                    done = true;
                    break;
            }
        }
    }
    return done;
}

void dan::api::Script::open(sol::state_view lua) {
    sol::usertype<Script> type = lua.new_usertype<Script>("Script",
        sol::constructors<Script(sol::this_state,sol::function,sol::variadic_args)>()
    );

    type["run"] = &Script::run;
}
