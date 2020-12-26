#ifndef DANZUN_API_MANIFEST_H_INCLUDED
#define DANZUN_API_MANIFEST_H_INCLUDED

#include <sol/sol.hpp>

namespace dan::api::manifest {
    void openAll(sol::state_view lua);
}

#endif
