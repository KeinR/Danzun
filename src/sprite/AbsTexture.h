#ifndef DANZUN_ABSTEXTURE_H_INCLUDED
#define DANZUN_ABSTEXTURE_H_INCLUDED

#include "AbsRenderConf.h"

namespace dan {
    class Context;
}

namespace dan {
    class AbsTexture: public AbsRenderConf {
    public:
        virtual ~AbsTexture() = 0;
        // Calls bind()
        void setup(Context &c) override;
        // Binds the texture's opengl object
        virtual void bind() = 0;
        // Renders the texture specific mesh
        virtual void render(Context &c) = 0;
    };
}

#endif
