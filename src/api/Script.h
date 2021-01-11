#ifndef DANZUN_API_SCRIPT_H_INCLUDED
#define DANZUN_API_SCRIPT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

namespace dan::api {
    /**
     * A sequence of lua code that is executed and paused until it finishes,
     * Implemented with lua coroutines. Pausing is done by yielding the number
     * of seconds to pause.
     * */
    class Script {
        /// The lua thread state
        sol::thread thread;
        /// The coroutine
        sol::coroutine routine;
        /// When the script should be executed next (game time)
        float timeOfNextRun;
        /// If the script should stop executing if it errors
        bool stopOnFail;
        /// If the script encountered an error (in execution)
        bool failed;
        /// If the script is finished
        bool done;
        std::vector<sol::object> args;
    public:
        /***
         * Default construction sets done to true, so it will not execute.
         * The object is in a safe state.
         * */
        Script();
        /**
         * Overload for the next one; converts pargs to a vector of objects ans passes it again as pargs
         * */
        Script(sol::this_state l, sol::function func, sol::variadic_args pargs);
        /**
         * Creates a script.
         * \param lua The current state
         * \param func The function to call (the script)
         * \param parsgs Arguments to forward to the function
         * */
        Script(sol::state_view lua, sol::function func, const std::vector<sol::object> &pargs);
        // Returns true if it's done
        /**
         * Try and execute the script.
         * Will only execute if:
         *      - game.getTime() >= timeOfNextRun
         *      - Not done
         *      - Not failed and not setStopOnFail
         * \param l The current state
         * \return true if \ref done is true
         * */
        bool run(sol::this_state l);

        /**
         * Check if it is set to stop on failure
         * \return true if yes
         * */
        bool isStopOnFail();
        /**
         * Check if the script failed in execution (the failure status)
         * \return true if yes
         * */
        bool isFailed();

        /**
         * Set if the script should stop on failure
         * \param v True if yes
         * */
        void setStopOnFail(bool v);
        /**
         * Set the failure status of the script.
         * */
        void setFailed(bool v);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view lua);
    };
}

#endif
