#ifndef DANZUN_RENDERABLE_H_INCLUDED
#define DANZUN_RENDERABLE_H_INCLUDED

namespace dan {
    class Context;
}

namespace dan {
    class Renderable {
    public:
        virtual ~Renderable() = 0;
        virtual void render(Context &c) = 0;
    };
}

#endif
