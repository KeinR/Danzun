#ifndef DANZUN_SPRITE_H_INCLUDED
#define DANZUN_SPRITE_H_INCLUDED

#include <memory>

#include "gfs/Texture.h"

namespace dan {
    class Sprite {
    public:
        typedef std::shared_ptr<Texture> texture_t;
    private:
        texture_t texture;
        int width; // pixels
        int height; // pixels
    public:
        Sprite();
        void setTexture(const texture_t &tex);
        void setWidth(int w);
        void setHeight(int h);
    };
}

#endif
