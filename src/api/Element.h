#ifndef DAN_API_ELEMENT_H_INCLUDED
#define DAN_API_ELEMENT_H_INCLUDED

#include <sol/sol.hpp>

#include "../game/Element.h"

namespace dan::api {
    class Element {
    public:
        typedef std::shared_ptr<::dan::Element> elem_t;
    private:
        elem_t elem;
        int renderPriority;
    public:
        Element(sol::this_state l, sol::function callback, sol::object self);

        elem_t getHandle() const;

        void render();
        void setRenderPriority(sol::this_state l, int value);
        void activate(sol::this_state l);
        void deactivate(sol::this_state l);

        static void open(sol::state_view lua);

    };
}

#endif
