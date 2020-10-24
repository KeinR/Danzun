#ifndef DANZUN_DEBUG_H_INCLUDED
#define DANZUN_DEBUG_H_INCLUDED

#ifndef NDEBUG
#   include <cassert>
#   include <iostream>
#   define DANZUN_ASSERT(cond) assert((cond))
#   define DANZUN_ASSERT_GL(msg) {if(::dan::db::checkGLError()){::std::cerr<<(msg)<<'\n';DANZUN_ASSERT(false);}}
#else
#   define DANZUN_ASSERT(cond) ((void)0)
#   define DANZUN_ASSERT_GL(msg) ((void)0)
#endif

namespace dan::db {
    bool checkGLError();
    const char *getGLErrorStr(int error);
}

#endif
