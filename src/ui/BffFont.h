#ifndef NOREN_BFFFONT_H_INCLUDED
#define NOREN_BFFFONT_H_INCLUDED

#include <array>
#include <string>
#include <vector>

#include "Font.h"

#include "../render/Texture.h"

namespace dan {
    class Mesh;
    class Color;
}

namespace dan {
    class BffFont: public Font {
    public:
        typedef unsigned char char_t;
    private:
        char_t startChar; // Inclusive
        char_t endChar; // Inclusive
        Texture atlas;
        std::array<char, 256> charWidths;
        std::array<float, 8> texBase;
        int cellWidth;
        int cellHeight;
        int rowSize;
        float texX;
        float texY;

        void getRenderData(
            std::vector<float> &vertices, std::vector<unsigned int> &indices,
            const std::string &str, const Color &color
        ) const;
    public:

        // Binary Font Format (.bff) font, Codehead's
        // Bitmap Font Generator's native output. 
        BffFont(const std::string &path);
        int getWidth(char_t c) const override;
        int getWidth(const std::string &str) const override;
        int getLinesWidth(const std::string &str) const override;
        int getHeight() const override;
        int getLinesHeight(const std::string &str) const override;

        void bindAtlas();

        // Will make newline when encountering \n char.
        Mesh genMesh(const std::string &str, const Color &color) const;
    };
}

#endif
