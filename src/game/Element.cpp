#include "Element.h"

#include "../core/error.h"

dan::Element::Element(sol::function callback, sol::object self):
    callback(callback), self(self) {
}

void dan::Element::doRender() {
    sol::function_result result = callback.call();
    if (!result.valid()) {
        sol::error msg = result;
        err("api::Element::render") << "callback.call() failed: " << msg.what();
    }
}

void dan::Element::render(Context &c) {
    doRender();
}
