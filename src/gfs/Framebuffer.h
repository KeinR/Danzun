#ifndef DANZUN_FRAMEBUFFER_H_INCLUDED
#define DANZUN_FRAMEBUFFER_H_INCLUDED

namespace dan {
    class Texture;
}

namespace dan {
    class Framebuffer {
        unsigned int handle;
        void steal(Framebuffer &other);
        void free();
    public:
        Framebuffer();
        Framebuffer(Framebuffer &&other);
        ~Framebuffer();
        Framebuffer &operator=(Framebuffer &&other);

        void attachTexture(Texture &tex);

        void bind() const;
    };
}

#endif
