#ifndef DAN_ELEMENT_H_INCLUDED
#define DAN_ELEMENT_H_INCLUDED

#include <sol/sol.hpp>

#include "../sprite/Renderable.h"

namespace dan {
    class Element: public Renderable {
        sol::function callback;
        sol::object self; // Can be whatever
    public:
        Element(sol::function callback, sol::object self);

        void doRender();
        // Calls doRender()
        void render(Context &c) override;
    };
}

#endif
