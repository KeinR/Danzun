#ifndef DANZUN_SPRITE_H_INCLUDED
#define DANZUN_SPRITE_H_INCLUDED

#include <memory>

#include "gfs/Texture.h"
#include "gfs/Matrix.h"

namespace dan {
    class Context;
}

namespace dan {
    class Sprite {
    public:
        typedef std::shared_ptr<Texture> texture_t;
    private:
        texture_t texture;
        // pixels
        Matrix mat;
    public:
        Sprite();
        void setTexture(const texture_t &tex);
        void setWidth(float w);
        void setHeight(float h);
        void setX(float x);
        void setY(float y);
        void render(Context &c);
    };
}

#endif
