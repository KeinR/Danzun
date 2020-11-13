#ifndef NOREN_IMAGE_H_INCLUDED
#define NOREN_IMAGE_H_INCLUDED

namespace dan {
    class Image {
    public:
        virtual ~Image() = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual int getChannels() const = 0;
        virtual int getSize() const = 0;
        virtual unsigned char *getData() const = 0;
    };
}

#endif
