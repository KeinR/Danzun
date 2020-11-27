#include "Data.h"

#include "../render/Texture.h"
#include "../sprite/Atlas.h"

dan::Data::Data() {
    
}
void dan::Data::loadImage(const std::string name, const std::string &path) {
    if (textures.find(name) == textures.end()) {
        std::shared_ptr<Texture> tex = std::make_shared<Texture>();
        tex->loadImage(path);
        textures[name] = tex;
    }
}
void dan::Data::loadAseprite(const std::string name, const std::string &path) {
    if (animations.find(name) == animations.end()) {
        animations[name] = std::make_shared<Animation>(Atlas::loadAnimation(path));
    }
}
void dan::Data::loadShader(const std::string name, const std::string &vert, const std::string &frag) {
    if (shaders.find(name) == shaders.end()) {
        shaders[name] = std::make_shared<Shader>(vert, frag);
    }
}

dan::Data::shader_t dan::Data::getShader(const std::string &name) {
    return shaders[name];
}
