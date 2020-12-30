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
        bool failed;
    public:
        Image(sol::this_state l, const std::string &path);
        Image(sol::this_state l, const std::string &path, bool loadFlipped);

        void bind();

        int getWidth();
        int getHeight();
        bool isFailed();

        static void open(sol::state_view lua);
    };
}

#endif
