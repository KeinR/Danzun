#ifndef DAN_ELEMENT_H_INCLUDED
#define DAN_ELEMENT_H_INCLUDED

#include <sol/sol.hpp>

#include "Renderable.h"
#include "../api/Entity.h"

namespace dan {
    class Element: public Renderable {
        sol::function callback;
        sol::object self; // Can be whatever
    public:
        Element(sol::function callback, sol::object self);

        void doRender();
        void augRender(const api::Entity &self0);
        // Calls doRender()
        void render(Context &c) override;
    };
}

#endif
