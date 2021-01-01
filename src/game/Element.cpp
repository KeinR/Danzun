#include "Element.h"

#include "../core/error.h"

dan::Element::Element(sol::function callback, const std::vector<sol::object> &self):
    callback(callback), self(self) {
}

void dan::Element::doRender() {
    sol::function_result result = callback.call(sol::as_args(self));
    if (!result.valid()) {
        sol::error msg = result;
        err("api::Element::doRender") << "Element callback failed: " << msg.what();
    }
}

void dan::Element::augRender(const api::Entity &self0) {
    sol::function_result result = callback.call(sol::as_args(self), self0);
    if (!result.valid()) {
        sol::error msg = result;
        err("api::Element::augRender") << "Element (entity) callback failed: " << msg.what();
    }
}

void dan::Element::render(Context &c) {
    doRender();
}
