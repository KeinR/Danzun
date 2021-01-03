#ifndef DANZUN_API_MESH_H_INCLUDED
#define DANZUN_API_MESH_H_INCLUDED

#include <sol/sol.hpp>

#include "../render/Mesh.h"

namespace dan::api {
    class Mesh {
        ::dan::Mesh mesh;
    public:
        Mesh(sol::this_state l);
        Mesh(::dan::Mesh &&omesh);
        void setVertices(sol::this_state l, sol::table rawData);
        void setIndices(sol::this_state l, sol::table rawData);
        void setParam(sol::this_state l, unsigned int index, int size, int stride, int offset);
        void render(sol::this_state l);

        static void open(sol::state_view &lua);
    };
}

#endif
