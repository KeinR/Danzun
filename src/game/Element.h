#ifndef DANZUN_ELEMENT_H_INCLUDED
#define DANZUN_ELEMENT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "Renderable.h"
#include "../api/Entity.h"

namespace dan {
    /**
     * A single renderable element.
     * The most basic of renderable types.
     * */
    class Element: public Renderable {
        /// The callback
        sol::function callback;
        /// Arguments to forward to the callback
        std::vector<sol::object> self;
    public:
        /**
         * Create an element.
         * \param callback The callback
         * \param self Arguments to forward to the callback
         * */
        Element(sol::function callback, const std::vector<sol::object> &self);

        /**
         * Render the element (call the callback)
         * */
        void doRender();
        /**
         * Like \ref doRender, except appents an extra userdata argument (entity) to the argument list.
         * */
        void augRender(const api::Entity &self0);
        /**
         * Calls \ref doRender
         * */
        void render(Context &c) override;
    };
}

#endif
