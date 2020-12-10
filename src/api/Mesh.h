#ifndef DANZUN_API_MESH_H_INCLUDED
#define DANZUN_API_MESH_H_INCLUDED

#include <sol/sol.hpp>

#include "../render/Mesh.h"

namespace dan::api::mesh {
    class Mesh {
        ::dan::Mesh mesh;
    public:
        Mesh();
        void setVertices(sol::table data);
        void setIndices(sol::table data);
        void setParam(unsigned int index, int size, int stride, int offset);
        void render();

        static void open(sol::state_view &lua);
    };
}

#endif
