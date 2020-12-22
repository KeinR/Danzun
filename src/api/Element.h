#ifndef DAN_API_ELEMENT_H_INCLUDED
#define DAN_API_ELEMENT_H_INCLUDED

#include <sol/sol.hpp>

#include "../game/Element.h"

namespace dan::api {
    class Element {
        std::shared_ptr<::dan::Element> elem;
        int renderPriority;
    public:
        Element(sol::this_state l, int renderPriority, sol::function callback, sol::object self);

        void render();
        void setRenderPriority(sol::this_state l, int value);
        void activate(sol::this_state l);
        void deactivate(sol::this_state l);

        static void open(sol::state_view lua);

    };
}

#endif
