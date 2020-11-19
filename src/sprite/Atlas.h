#ifndef DANZUN_ATLAS_H_INCLUDED
#define DANZUN_ATLAS_H_INCLUDED

#include <memory>
#include <vector>
#include <array>
#include <map>

#include "../render/Texture.h"
#include "../ani/Animation.h"

namespace dan {
    class AniControl;
}

namespace dan {
    class Atlas {
    public:
        struct frame {
            int width;
            int height;
            std::array<float, 8> coords;
            // Seconds
            float duration;
        };
    private:
        typedef std::map<std::string, unsigned int> frameMap_t;
        std::vector<frame> frames;
        frameMap_t frameMap;
        std::shared_ptr<Texture> texture;
    public:
        Atlas();
        // Data MUST be formatted as json-array
        // Returns *this
        Atlas &loadAse(const std::string &dataPath);

        std::shared_ptr<Texture> &getTexture();
        frame &getFrame(unsigned int index);
        frame &getFrame(const std::string &name);

        Animation asAnimation() const;

        // Aseprite spritesheet animation
        static Animation loadAnimation(const std::string &path);
    };
}

#endif
