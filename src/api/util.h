#ifndef DANZUN_API_UTIL_H_INCLUDED
#define DANZUN_API_UTIL_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

/**
 * Simple utility functions that dpn't belong to any
 * particular class
 * */
namespace dan::api::util {
    /**
     * Parse Aseprite JSON metadata
     *
     * The format of the returned table is as follows:
     *
     * result = {
     *     array = {
     *         1 = { // Metadata about chunk
     *             width = number,
     *             height = number,
     *             duration = number,
     *             coords = number[16]
     *         },
     *         2 = ...
     *         3 = ...
     *         ...
     *     },
     *     hash = {
     *          foo = 2, // Names of chunks pointing to their chunks.
     *                      NOTE: If the name ends in .ase, the exrension (.ase)
     *                      will be stripped!
     *          bar = ...,
     *          ...
     *     }
     * }
     *
     * \param l The current state
     * \param path Path to the JSON file
     * */
    sol::table loadAsepriteJSONArray(sol::this_state l, const std::string &path);

    /**
     * Registers the namespace with the given state
     * \param lua The state
     * */
    void open(sol::state_view lua);
}

#endif
