#ifndef DANZUN_API_SHADER_H_INCLUDED
#define DANZUN_API_SHADER_H_INCLUDED

#include <sol/sol.hpp>

#include "../render/Shader.h"

namespace dan::api {
    class Shader {
        ::dan::Shader shader;
    public:
        Shader(sol::this_state l, const std::string &vertex, const std::string &fragment);

        void setInt1(sol::this_state l, const std::string &name, int value);
        void use(sol::this_state l);

        static void open(sol::state_view &lua);
    };
}

#endif
