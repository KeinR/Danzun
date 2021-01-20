#ifndef DANZUN_EFFECT_H_INCLUDED
#define DANZUN_EFFECT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "Renderable.h"

namespace dan {
    /**
     * A single effect "type" that can have multible instances, allowing for efficient
     * batch rendering
     * */
    class Effect: public Renderable {
        /// Type of the objects
        typedef std::vector<sol::table> objects_t;
        /// Type of the arguments
        typedef std::vector<sol::object> args_t;
        /// The ser forwarded arguments (so can be zero in size)
        args_t args;
        /// The effect instances
        objects_t objects;
        /// The callback
        sol::function callback;
        /// The render priority
        int renderPriority;
        /// If the lua reference has been deleted
        bool detached;
    public:
        /**
         * Create a new effect
         * \param args The arguments to forward to the callback
         * \param callback The callback
         * */
        Effect(int priority, args_t args, sol::function callback);

        /**
         * Set if the lua reference has been deleted
         * This should only be called from the lua wapper class's destructor
         * (see api/Effect)
         * \param value The value
         * */
        void setDetached(bool value);

        /**
         * Sets the render priority of this effect
         * \param value The value
         * */
        void setRenderPriority(int value);
        /**
         * \return This element's render priorit
         * */
        int getRenderPriority();

        /**
         * Adds a new object as an instance of this effect
         * \param obj The object
         * */
        void spawn(sol::object obj);

        /**
         * Calls the callback with the forwarded arguments and the instances.
         * A table with all the objects (instances) added through
         * \ref spawn are appended to the argument list.
         * \param c The render context
         * */
        void render(Context &c) override;
    };
}

#endif
