#include "Matrix.h"

#include "../core/Context.h"
#include "../render/Matrix.h"

dan::api::Matrix::Matrix(): x(0), y(0), width(10), height(10), rotation(0) {
}
void dan::api::Matrix::load(sol::this_state l) {
    ::dan::Matrix(x, y, width, height, rotation).load(Context::fromLua(l));
}

void dan::api::Matrix::open(sol::state_view &lua) {
    sol::usertype<Matrix> type = lua.new_usertype<Matrix>("Matrix",
        sol::constructors<Matrix()>()
    );

    type["x"] = &Matrix::x;
    type["y"] = &Matrix::y;
    type["width"] = &Matrix::height;
    type["height"] = &Matrix::width;
    type["rotation"] = &Matrix::rotation;
    type["load"] = &Matrix::load;
}
