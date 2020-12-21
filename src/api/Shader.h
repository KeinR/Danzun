#ifndef DANZUN_API_SHADER_H_INCLUDED
#define DANZUN_API_SHADER_H_INCLUDED

#include <array>

#include <sol/sol.hpp>

#include "../render/Shader.h"

namespace dan::api {
    class Shader {
        ::dan::Shader shader;
    public:
        Shader(sol::this_state l, const std::string &vertex, const std::string &fragment);

        // Last param forces at least one value
        void setInt(const std::string &name, sol::variadic_args values, int);
        void setFloat(const std::string &name, sol::variadic_args values, float);

        void setMat4(const std::string &name, const std::array<float, 16> &values);

        void use();

        static void open(sol::state_view &lua);
    };
}

#endif
