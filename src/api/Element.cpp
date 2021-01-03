#include "Element.h"

#include <vector>

#include "../game/Game.h"

dan::api::Element::Element(sol::this_state l, sol::function callback, sol::variadic_args self):
    elem(std::make_shared<::dan::Element>(callback, std::vector<sol::object>(self.begin(), self.end()))), renderPriority(0)
{
}

dan::api::Element::elem_t dan::api::Element::getHandle() const {
    return elem;
}

void dan::api::Element::render() {
    elem->doRender();
}

void dan::api::Element::setRenderPriority(sol::this_state l, int value) {
    deactivate(l);
    renderPriority = value;
    activate(l);
}
void dan::api::Element::activate(sol::this_state l) {
    Game::fromLua(l).submitRenderable(renderPriority, elem);
}
void dan::api::Element::deactivate(sol::this_state l) {
    Game::fromLua(l).removeRenderable(elem.get());
}

// Static members

void dan::api::Element::open(sol::state_view lua) {
    sol::usertype<Element> type = lua.new_usertype<Element>("Element",
        sol::constructors<Element(sol::this_state,sol::function,sol::variadic_args)>()
    );

    type["render"] = &Element::render;
    type["setRenderPriority"] = &Element::setRenderPriority;
    type["activate"] = &Element::activate;
    type["deactivate"] = &Element::deactivate;
}

