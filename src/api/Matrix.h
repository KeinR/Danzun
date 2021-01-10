#ifndef DANZUN_API_MATRIX_H_INCLUDED
#define DANZUN_API_MATRIX_H_INCLUDED

#include <sol/sol.hpp>

namespace dan::api {
    /**
     * An abstraction over the classic matrix to allow for smoother
     * code.
     * */
    class Matrix {
        /// The center x coordinate
        float x;
        /// The center y coordinate
        float y;
        /// The x coordinate of the rotation pivot
        float pivotXOfs;
        /// The y coordinate of the rotation pivot
        float pivotYOfs;
        /// The width
        float width;
        /// The height
        float height;
        /// The rotation (radians)
        float rotation;
        /// If it should be flipped horizontally
        bool flipHorizontal;
    public:
        /**
         * Construct a matrix, defaulting parameters.
         * */
        Matrix();
        /**
         * Construct the matrix with values from the given table.
         * Any values that are not found or of invalid type are defaulted.
         * \param t The table
         * */
        Matrix(sol::table t);

        /**
         * Load the matrix into the given uniform
         * \param l The current state
         * \param name The name of the uniform
         * */
        void load2(sol::this_state l, const std::string &name);
        /***
         * Overload for \ref load2 that sets the uniform name as "model"
         * */
        void load(sol::this_state l);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
