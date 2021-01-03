#ifndef DANZUN_UTIL_H_INCLUDED
#define DANZUN_UTIL_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan::ut {
    std::string lowercase(const std::string &in);
    void checkGLError(const char *sig, sol::state_view lua);
    void checkALError(const char *sig, sol::state_view lua);
}

#endif
