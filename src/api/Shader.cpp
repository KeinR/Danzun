#include "Shader.h"

#include "../core/Context.h"

dan::api::Shader::Shader(sol::this_state l, const std::string &vertex, const std::string &fragment):
    shader(Context::fromLua(l), vertex, fragment) {
}

void dan::api::Shader::setInt1(sol::this_state l, const std::string &name, int value) {
    shader.setInt1(Context::fromLua(l), name, value);
}
void dan::api::Shader::use(sol::this_state l) {
    Context::fromLua(l).setShader(shader);
}

// static members

void dan::api::Shader::open(sol::state_view &lua) {

}
