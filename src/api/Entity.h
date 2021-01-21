#ifndef DANZUN_API_ENTITY_H_INCLUDED
#define DANZUN_API_ENTITY_H_INCLUDED

#include <memory>
#include <set>
#include <string>

#include <sol/sol.hpp>

#include "Script.h"

namespace dan {
    namespace api {
        class Element;
    }
    class Entity;
}

namespace dan::api {
    /**
     * A single reference to an entity, of many.
     * Entities are registered with the master game class.
     * This is just a interface.
     * */
    class Entity {
    public:
        /// The handle type
        typedef std::shared_ptr<::dan::Entity> handle_t;
    private:
        /// Handle to the entity
        handle_t handle;
    public:
        /**
         * Construct with an existing entity
         * \param v The entity
         * */
        Entity(const handle_t &v);
        /**
         * Construct, creating a new entity and registering it.
         * \param l The current state
         * \param hitCallback Function to call upon collisions. The first parameter will be this entity, the second the one it it.
         * \param disp The element to render. This entity is appended to the argument list (at call)
         * \param equation Formula representing the path of the entity
         * \param vars Variable tables to regsiter with the expression 
         * */
        Entity(sol::this_state l, int priority,
            sol::function hitCallback, const Element &disp,
            const std::string &equation, sol::variadic_args vars);

        /**
         * Gets the handle
         * \return The handle
         * */
        handle_t getHandle();

        /**
         * Sets the script for this entity
         * \param s The script
         * */
        void setScript(const Script &s);

        /**
         * Adds this entity to the render loop, if it's not added already
         * \param l The current state
         * */
        void activate(sol::this_state l);
        /**
         * Removes this entity from the rener loop, if it was added
         * \param l The current state
         * */
        void deactivate(sol::this_state l);
        /**
         * Sets the render priority of the entity
         * \param value The new priority
         * */
        void setRenderPriority(sol::this_state l, int value);

        /**
         * Registers a new circle hitbox for this entity
         * \param l The current state
         * \param group The hitbox group
         * */
        void regCircle(sol::this_state l, const std::string &group);
        /**
         * Registers a new polygon hitbox for this entity
         * \note The points must be an array, even in length, of x/y pairs, and have values in the
         * range of [-1, 1]
         * \param l The current state
         * \param group The hitbox group
         * \param points The points for the hitbox
         * */
        void regPolygon(sol::this_state l, const std::string &group, sol::table points);
        /**
         * Deletes all of this entity's hitboxes
         * \param l The current state
         * */
        void unregHitboxes(sol::this_state l);

        /**
         * Gets the value of a variable from the expression's symbol table.
         * Used as the __index metamethod (foo.bar).
         * \param name The name of the variable
         * \return The value of the variable, 0 if it doesn't exist.
         * */
        float index(const std::string &name);
        /**
         * Sets the value of a variable from the expressions sybol table.
         * Used as the __new_index metamethod (foo.bar = 4).
         * Does nothing if the variable does not exist.
         * \param name The variable name
         * \param value The new value
         * */
        void newIndex(const std::string &name, float value);
        /**'
         * Overload for \ref newIndex that performs a static cast of the bool to a float.
         * */
        void newIndexBool(const std::string &name, bool value);

        sol::table getTable(sol::this_state l);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
