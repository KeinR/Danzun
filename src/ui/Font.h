#ifndef DANZUN_FONT_H_INCLUDED
#define DANZUN_FONT_H_INCLUDED

#include <string>

#include "../render/Mesh.h"

namespace dan {
    class Color;
}

namespace dan {
    class Font {
    public:
        virtual ~Font() = 0;
        virtual int getWidth(unsigned char c) const = 0;
        virtual int getWidth(const std::string &str) const = 0;
        virtual int getLinesWidth(const std::string &str) const = 0;
        virtual int getHeight() const = 0;
        virtual int getLinesHeight(const std::string &str) const = 0;
        virtual Mesh genMesh(const std::string &str, const Color &color) const = 0;
    };
}

#endif
