#ifndef DANZUN_SPRITE_H_INCLUDED
#define DANZUN_SPRITE_H_INCLUDED

#include <memory>

#include "AbsRenderConf.h"

#include "../render/Matrix.h"

namespace dan {
    class Context;
    class Shader;
}

namespace dan {
    class Sprite {
    public:
        typedef std::shared_ptr<AbsRenderConf> conf_t;
    private:
        conf_t conf;
        // pixels
        Matrix mat;
    public:
        Sprite();

        void setConf(const conf_t &cf);

        void setWidth(float w);
        void setHeight(float h);
        void setX(float x);
        void setY(float y);
        void setCenterX(float x);
        void setCenterY(float y);
        // radians
        void setRotation(float r);

        int getWidth() const;
        int getHeight() const;
        int getX() const;
        int getY() const;
        float getRotation() const;

        void render(Context &c);
    };
}

#endif
