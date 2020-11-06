#ifndef DANZUN_ABSTEXTURE_H_INCLUDED
#define DANZUN_ABSTEXTURE_H_INCLUDED

namespace dan {
    class Context;
}

namespace dan {
    class AbsTexture {
    public:
        virtual ~AbsTexture() = 0;
        virtual void bind() = 0;
        virtual void render(Context &c) = 0;
    };
}

#endif
