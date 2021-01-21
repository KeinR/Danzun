#ifndef DANZUN_FRAMEBUFFER_H_INCLUDED
#define DANZUN_FRAMEBUFFER_H_INCLUDED

namespace dan {
    class Texture;
}

namespace dan {
    class Framebuffer {
        unsigned int handle;
    public:
        Framebuffer();
        ~Framebuffer();
        // DOn't bother
        Framebuffer(Framebuffer&&) = delete;

        void attachTex(Texture &tex);
        bool complete();
        void bind();

        static void bindDefault();
    };
}


#endif

