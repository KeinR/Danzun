#include "Shader.h"

#include "../core/Context.h"

dan::api::Shader::Shader(sol::this_state l, const std::string &vertex, const std::string &fragment):
    shader(Context::fromLua(l), vertex, fragment) {
}

void dan::api::Shader::setInt(const std::string &name, sol::variadic_args values, int) {
    switch (values.size()) {
        // case 0: // Impossible
        case 1:
            shader.set1i(name,
                values.get<int>(0)
            );
            break;
        case 2:
            shader.set2i(name,
                values.get<int>(0),
                values.get<int>(1)
            );
            break;
        case 3:
            shader.set3i(name,
                values.get<int>(0),
                values.get<int>(1),
                values.get<int>(2)
            );
            break;
        // case 4: // Fallthrough
        default: // In this case, ignore trailing values
            shader.set4i(name,
                values.get<int>(0),
                values.get<int>(1),
                values.get<int>(2),
                values.get<int>(3)
            );
            break;
    }
}

void dan::api::Shader::setFloat(const std::string &name, sol::variadic_args values, float) {
    switch (values.size()) {
        // case 0: // Impossible
        case 1:
            shader.set1f(name,
                values.get<float>(0)
            );
            break;
        case 2:
            shader.set2f(name,
                values.get<float>(0),
                values.get<float>(1)
            );
            break;
        case 3:
            shader.set3f(name,
                values.get<float>(0),
                values.get<float>(1),
                values.get<float>(2)
            );
            break;
        // case 4: // Fallthrough
        default: // In this case, ignore trailing values
            shader.set4f(name,
                values.get<float>(0),
                values.get<float>(1),
                values.get<float>(2),
                values.get<float>(3)
            );
            break;
    }
}

void dan::api::Shader::setMat4(const std::string &name, const std::array<float, 16> &values) {
    shader.setMatrix4fv(name, values.data());
}

void dan::api::Shader::use() {
    shader.use();
}

// static members

void dan::api::Shader::open(sol::state_view &lua) {
    sol::usertype<Shader> type = lua.new_usertype<Shader>("Shader",
        sol::constructors<Shader(sol::this_state,const std::string&,const std::string&)>()
    );

    type["setInt"] = &Shader::setInt;
    type["setFloat"] = &Shader::setFloat;
    type["setMat4"] = &Shader::setMat4;
    type["use"] = &Shader::use;
}
