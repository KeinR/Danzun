#ifndef DANZUN_RENDERABLE_H_INCLUDED
#define DANZUN_RENDERABLE_H_INCLUDED

namespace dan {
    class Context;
}

namespace dan {
    /**
     * A single renderable object
     * */
    class Renderable {
    public:
        virtual ~Renderable() = 0;
        /**
         * Render the object
         * \param c The render context
         * */
        virtual void render(Context &c) = 0;
    };
}

#endif
