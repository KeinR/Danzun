#ifndef DANZUN_API_MATRIX_H_INCLUDED
#define DANZUN_API_MATRIX_H_INCLUDED

#include <sol/sol.hpp>

namespace dan::api {
    class Matrix {
        float x;
        float y;
        float pivotXOfs;
        float pivotYOfs;
        float width;
        float height;
        float rotation;
    public:
        Matrix();
        Matrix(sol::table t);
        void load(sol::this_state l);

        static void open(sol::state_view &lua);
    };
}

#endif
