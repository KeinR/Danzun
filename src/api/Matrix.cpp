#include "Matrix.h"

#include <string>

#include "../core/Context.h"
#include "../render/Matrix.h"

dan::api::Matrix::Matrix(): x(0), y(0), pivotXOfs(0), pivotYOfs(0), width(10), height(10), rotation(0) {
}
dan::api::Matrix::Matrix(sol::table t): Matrix() {
    x = t["x"].get_or<float>(x);
    y = t["y"].get_or<float>(y);
    pivotXOfs = t["pivotX"].get_or<float>(pivotXOfs);
    pivotYOfs = t["pivotY"].get_or<float>(pivotYOfs);
    width = t["width"].get_or<float>(width);
    height = t["height"].get_or<float>(height);
    rotation = t["rotation"].get_or<float>(rotation);
}
void dan::api::Matrix::load(sol::this_state l) {
    ::dan::Matrix(x, y, pivotXOfs, pivotYOfs, width, height, rotation, false).load(Context::fromLua(l));
}
void dan::api::Matrix::load2(sol::this_state l, const std::string &name) {
	::dan::Matrix(x, y, pivotXOfs, pivotYOfs, width, height, rotation, false).load(Context::fromLua(l), name);
}

void dan::api::Matrix::open(sol::state_view &lua) {
    sol::usertype<Matrix> type = lua.new_usertype<Matrix>("Matrix",
        sol::constructors<Matrix(), Matrix(sol::table)>()
    );

    type["x"] = &Matrix::x;
    type["y"] = &Matrix::y;
    type["pivotX"] = &Matrix::pivotXOfs;
    type["pivotY"] = &Matrix::pivotYOfs;
    type["width"] = &Matrix::width;
    type["height"] = &Matrix::height;
    type["rotation"] = &Matrix::rotation;
    type["load"] = sol::overload(&Matrix::load, &Matrix::load2);
}
