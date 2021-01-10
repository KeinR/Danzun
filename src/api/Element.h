#ifndef DANZUN_API_ELEMENT_H_INCLUDED
#define DANZUN_API_ELEMENT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "../game/Element.h"

namespace dan::api {
    /**
     * A single renderable entity.
     * Can be added to the main render loop and little else.
     * */
    class Element {
    public:
        typedef std::shared_ptr<::dan::Element> elem_t;
    private:
        /// Handle to the element
        elem_t elem;
        /// The render priprity
        int renderPriority;
        /// If the element is currently in the render loop
        bool activated;
    public:
        /**
         * Creates al element
         * \param l The current state
         * \param callback The callback to call while rendering
         * \param args Arguments to forward to the callback. These will always be in front.
         * */
        Element(sol::this_state l, sol::function callback, sol::variadic_args args);

        /**
         * Gets underlying handle
         * \return The handle
         * */
        elem_t getHandle() const;

        /**
         * Calls the callback
         * */
        void render();
        /**
         * Changes the render priority
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
         * Removes from the render loop if it was added previously
         * */
        void deactivate(sol::this_state l);

        /**
         * Registers with the provided state
         * \param lua The state
         * */
        static void open(sol::state_view lua);

    };
}

#endif
