#ifndef DANZUN_ATLAS_H_INCLUDED
#define DANZUN_ATLAS_H_INCLUDED

#include <memory>
#include <vector>
#include <array>
#include <map>

#include "gfs/Texture.h"

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
        void loadAse(const std::string &dataPath);

        std::shared_ptr<Texture> &getTexture();
        frame &getFrame(unsigned int index);
        frame &getFrame(const std::string &name);
    };
}

#endif
