#include "Data.h"

#include "../render/Texture.h"
#include "../sprite/Atlas.h"

dan::Data::Data(Context &c): c(&c), shaderId(0) {
}
void dan::Data::loadImage(const std::string &name, const std::string &path) {
    if (textures.find(name) == textures.end()) {
        std::shared_ptr<Texture> tex = std::make_shared<Texture>();
        tex->loadImage(path);
        textures[name] = tex;
    }
}
void dan::Data::loadAseprite(const std::string &name, const std::string &path) {
    if (animations.find(name) == animations.end()) {
        animations[name] = std::make_shared<Animation>(Atlas::loadAnimation(path));
    }
}
int dan::Data::loadShader(const std::string &vert, const std::string &frag) {
    shaders[++shaderId] = Shader(*c, vert, frag);
    return shaderId;
}

dan::Shader &dan::Data::getShader(int id) {
    return shaders[id];
}

void dan::Data::deleteShader(int id) {
    shaders.erase(id);
}
