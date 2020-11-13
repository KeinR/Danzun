#ifndef DANZUN_MANAGEDIMAGE_H_INCLUDED
#define DANZUN_MANAGEDIMAGE_H_INCLUDED

#include <string>

#include "Image.h"

namespace dan {
    class ManImage: public Image {
        unsigned char *data;
        int width;
        int height;
        int channels;
        void free();
        void steal(ManImage &other);
    public:
        /**
        * Zero initialize
        */
        ManImage();
        /**
        * From file.
        * desiredChannels at 0 for no preference (taken on load)
        */
        ManImage(const std::string &path, bool flipOnLoad = true, int desiredChannels = 0);
        ManImage(ManImage &&other);
        ~ManImage() override;
        ManImage &operator=(ManImage &&other);

        int getWidth() const override;
        int getHeight() const override;
        int getChannels() const override;
        int getSize() const override;
        unsigned char *getData() const override;
    };
}

#endif
