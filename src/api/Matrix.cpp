#include "Matrix.h"

#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "../core/Context.h"
#include "../render/Matrix.h"
#include "../core/util.h"

dan::api::Matrix::Matrix(): x(0), y(0), pivotXOfs(0), pivotYOfs(0), width(10), height(10), rotation(0), flipHorizontal(false) {
}
dan::api::Matrix::Matrix(sol::table t): Matrix() {
    x = t["x"].get_or<float>(x);
    y = t["y"].get_or<float>(y);
    pivotXOfs = t["pivotX"].get_or<float>(pivotXOfs);
    pivotYOfs = t["pivotY"].get_or<float>(pivotYOfs);
    width = t["width"].get_or<float>(width);
    height = t["height"].get_or<float>(height);
    rotation = t["rotation"].get_or<float>(rotation);
    flipHorizontal = t["flipHorizontal"].get_or<bool>(flipHorizontal);
}
void dan::api::Matrix::load(sol::this_state l) {
    load2(l, "model");
}
void dan::api::Matrix::load2(sol::this_state l, const std::string &name) {
    ::dan::Matrix(x, y, pivotXOfs, pivotYOfs, width, height, rotation, flipHorizontal).load(Context::fromLua(l), name);
    ut::checkGLError("api::Matrix::load2", l);
}

sol::table dan::api::Matrix::getData(sol::this_state l) {
    sol::state_view lua = l;
    sol::table result = lua.create_table();
    glm::mat4 matrix = ::dan::Matrix(x, y, pivotXOfs, pivotYOfs, width, height, rotation, flipHorizontal).getData(Context::fromLua(l));
    auto data = glm::value_ptr(matrix);
    for (int i = 0; i < 4*4; i++) {
        result.add(data[i]);
    }
    return result;
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
    type["flipHorizontal"] = &Matrix::flipHorizontal;
    type["load"] = sol::overload(&Matrix::load, &Matrix::load2);
    type["getData"] = &Matrix::getData;
}

