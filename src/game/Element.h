#ifndef DANZUN_ELEMENT_H_INCLUDED
#define DANZUN_ELEMENT_H_INCLUDED

#include <vector>

#include <sol/sol.hpp>

#include "Renderable.h"
#include "../api/Entity.h"

namespace dan {
    class Element: public Renderable {
        sol::function callback;
        std::vector<sol::object> self;
    public:
        Element(sol::function callback, const std::vector<sol::object> &self);

        void doRender();
        void augRender(const api::Entity &self0);
        // Calls doRender()
        void render(Context &c) override;
    };
}

#endif
