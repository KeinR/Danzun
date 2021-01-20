#ifndef DANZUN_API_MESH_H_INCLUDED
#define DANZUN_API_MESH_H_INCLUDED

#include <sol/sol.hpp>

#include "../render/Mesh.h"

namespace dan::api {
    /**
     * A collection of vertices, indices, and metadata on how the vertices are structured.
     * Internally, has a vertex array, vertex buffer, and element buffer.
     * Used to interface with the actual mesh class.
     * */
    class Mesh {
        /// The mesh
        ::dan::Mesh mesh;
    public:
        /**
         * Create a new mesh
         * \param l The current state
         * */
        Mesh(sol::this_state l);
        /**
         * Move a mesh
         * \param omesh The mesh to move
         * */
        Mesh(::dan::Mesh &&omesh);
        /**
         * Set the vertex data
         * \param l The current state
         * \param rawData The vertex data
         * */
        void setVertices(sol::this_state l, sol::table rawData);
        /**
         * Sets the element data
         * \param l The current state
         * \param rawData The element data
         * */
        void setIndices(sol::this_state l, sol::table rawData);
        /**
         * Set a vertex array parameter, and enable it.
         * \param l The current state
         * \param index The parameter index
         * \param size The size (elements) of the vertex
         * \param stride The number of elements that must be traversed to get to the next vertex
         * \param offset The index of the first vertex
         * */
        void setParam(sol::this_state l, unsigned int index, int size, int stride, int offset);
        /**
         * Renders the vertices with the provided indices.
         * \param l The current state
         * */
        void render(sol::this_state l);

        /**
         * Renders instanced
         * \param l The current state
         * \param count The number of instanced to render
         * */
        void renderInstanced(sol::this_state l, unsigned int count);

        /**
         * Register this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
