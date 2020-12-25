#ifndef DANZUN_API_IMAGE_H_INCLUDED
#define DANZUN_API_IMAGE_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

#include "../render/Texture.h"

namespace dan::api {
    class Image {
        ::dan::Texture tex;
        int width;
        int height;
    public:
        Image(const std::string &path);

        void bind();

        static void open(sol::state_view lua);
    };
}

#endif
