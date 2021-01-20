#ifndef DANZUN_API_EFFECT_H_INCLUDED
#define DANZUN_API_EFFECT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../game/Effect.h"

namespace dan::api {
    /**
     * Represents a single type of "effect".  Instances are created through \ref spawn, and all instances
     * are given to the callback as paramters, allowing for batch effect
     * processing.
     * The effect has its home in the master game class. It is only destructed after
     * the client handle (this class) is destructed and all effect instances have
     * been cleared.
     * */
    class Effect {
        /// Handle to the effect
        std::shared_ptr<::dan::Effect> effect;
        /// If the effect has been added to the render loop or not.
        /// prevents adding duplicates.
        bool activated;
    public:
        /**
         * Creates an effect with a callback and args
         * \param l The current state
         * \param callback Callback to call as part of the effect
         * \param args Arguments to forward to the callback
         * */
        Effect(sol::this_state l, int priority, sol::function callback, sol::variadic_args args);
        /**
         * Registers the effect as "detached",
         * telling it that it can expect no new effects and that it should
         * destruct as soon as it has no more
         * */
        ~Effect();

        /**
         * Creates an effect
         * \param obj The object parameter
         * */
        void spawn(sol::table obj);
        /**
         * Sets the rendering priority
         * \param l The current state
         * \param value The new priority
         * */
        void setRenderPriority(sol::this_state l, int value);
        /**
         * Adds to the render loop of not already
         * \param l The current state
         * */
        void activate(sol::this_state l);
        /**
         * Removes from the render loop of previously added
         * \param l The current state
         * */
        void deactivate(sol::this_state l);

        /**
         * Registers this class with a lua state
         * \param lua The Lua state
         * */
        static void open(sol::state_view lua);

    };
}

#endif
