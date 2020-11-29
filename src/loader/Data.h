#ifndef DANZUN_DATA_H_INCLUDED
#define DANZUN_DATA_H_INCLUDED

#include <string>
#include <memory>

#include "../ani/Animation.h"
#include "../render/Texture.h"
#include "../render/Shader.h"
#include "../ui/Font.h"

namespace dan {
    class Context;
}

namespace dan {
    class Data {
    public:
        typedef std::shared_ptr<Texture> texture_t;
        typedef std::shared_ptr<Animation> animation_t;
        typedef std::shared_ptr<Font> font_t;
    private:
        Context *c;
        std::map<std::string, texture_t> textures;
        std::map<std::string, animation_t> animations;
        int shaderId;
        std::map<std::string, Shader> shaders;
        std::map<std::string, font_t> fonts;
    public:
        Data(Context &c);
        void loadImage(const std::string &name, const std::string &path);
        void loadAseprite(const std::string &name, const std::string &path);
        int loadShader(const std::string &vert, const std::string &frag);

        Shader &getShader(int id);
        void deleteShader(int id);
    };
}

#endif



