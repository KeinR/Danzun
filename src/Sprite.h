#ifndef DANZUN_SPRITE_H_INCLUDED
#define DANZUN_SPRITE_H_INCLUDED

#include <memory>

#include "gfs/Texture.h"
#include "gfs/Matrix.h"

namespace dan {
    class Context;
    class Shader;
}

namespace dan {
    class Sprite {
    public:
        typedef std::shared_ptr<Texture> texture_t;
        typedef std::shared_ptr<Shader> shader_t;
    private:
        texture_t texture;
        // pixels
        Matrix mat;
        // The preferred shader
        std::shared_ptr<Shader> shader;
    public:
        Sprite();

        void setTexture(const texture_t &tex);

        void setWidth(float w);
        void setHeight(float h);
        void setX(float x);
        void setY(float y);

        int getWidth() const;
        int getHeight() const;
        int getX() const;
        int getY() const;

        // nullptr for no preference / use the one currently bound.
        // nullptr by default
        void setShader(const shader_t &s);

        void render(Context &c);
    };
}

#endif
