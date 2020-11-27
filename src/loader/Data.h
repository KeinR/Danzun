#ifndef DANZUN_DATA_H_INCLUDED
#define DANZUN_DATA_H_INCLUDED

#include <string>
#include <memory>

#include "../ani/Animation.h"
#include "../render/Texture.h"
#include "../render/Shader.h"
#include "../ui/Font.h"

namespace dan {
    class Data {
    public:
        typedef std::shared_ptr<Texture> texture_t;
        typedef std::shared_ptr<Animation> animation_t;
        typedef std::shared_ptr<Shader> shader_t;
        typedef std::shared_ptr<Font> font_t;
    private:
        std::map<std::string, texture_t> textures;
        std::map<std::string, animation_t> animations;
        std::map<std::string, shader_t> shaders;
        std::map<std::string, font_t> fonts;
    public:
        Data();
        void loadImage(const std::string name, const std::string &path);
        void loadAseprite(const std::string name, const std::string &path);
        void loadShader(const std::string name, const std::string &vert, const std::string &frag);

        shader_t getShader(const std::string &name);
    };
}

#endif



