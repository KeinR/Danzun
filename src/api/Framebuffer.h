#ifndef DANZUN_API_FRAMEBUFFER_H_INCLUDED
#define DANZUN_API_FRAMEBUFFER_H_INCLUDED

#include <sol/sol.hpp>

#include "../render/Framebuffer.h"
#include "../render/Texture.h"

namespace dan::api {
    class Framebuffer {
        Texture tex;
        ::dan::Framebuffer buf;
        int width;
        int height;
    public:
        Framebuffer(sol::this_state l, int width, int height);
        void bindBuf(sol::this_state l);
        void bindTex();

        static void clear();
        static void unbindBuf(sol::this_state l);
        static void open(sol::state_view l);
    };
}

#endif

