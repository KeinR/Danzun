#ifndef DAN_API_MATRIX_H_INCLUDED
#define DAN_API_MATRIX_H_INCLUDED

#include <sol/sol.hpp>

namespace dan::api {
    class Matrix {
        float x;
        float y;
        float width;
        float height;
        float rotation;
    public:
        Matrix();
        void load(sol::this_state l);

        static void open(sol::state_view &lua);
    };
}

#endif
