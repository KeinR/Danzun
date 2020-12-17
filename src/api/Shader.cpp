#include "Shader.h"

#include "../core/Context.h"

dan::api::Shader::Shader(sol::this_state l, const std::string &vertex, const std::string &fragment):
    shader(Context::fromLua(l), vertex, fragment) {
}

void dan::api::Shader::setInt1(const std::string &name, int value) {
    shader.setInt1(name, value);
}
void dan::api::Shader::use() {
    shader.use();
}

// static members

void dan::api::Shader::open(sol::state_view &lua) {
    sol::usertype<Shader> type = lua.new_usertype<Shader>("Shader",
        sol::constructors<Shader(sol::this_state,const std::string&,const std::string&)>()
    );

    type["setInt1"] = &Shader::setInt1;
    type["use"] = &Shader::use;

}
