#ifndef DAN_LUAREF_H_INCLUDED
#define DAN_LUAREF_H_INCLUDED

#include <sol/sol.hpp>

namespace dan {
    template<typename T>
    class LuaRef {
        sol::userdata ref;
        T *ptr;
    public:
        // Expects type to be valid
        LuaRef(sol::userdata ref);
        T &operator*();
        T *operator->();
    };
}

#include "LuaRef.inl"

#endif
