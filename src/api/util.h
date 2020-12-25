#ifndef DAN_API_UTIL_H_INCLUDED
#define DAN_API_UTIL_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan::api::util {
    sol::table loadAsepriteJSONArray(sol::this_state l, const std::string &path);

    void open(sol::state_view lua);
}

#endif
