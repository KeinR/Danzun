#include "ImgDisp.h"

#include "../core/Context.h"

dan::ImgDisp::ImgDisp(const texture_t &texture, Shader *shader):
    texture(texture), shader(shader)
{
}
void dan::ImgDisp::setTexture(const texture_t &texture) {
    this->texture = texture;
}
void dan::ImgDisp::setShader(Shader *shader) {
    this->shader = shader;
}
dan::ImgDisp::texture_t &dan::ImgDisp::getTexture() {
    return texture;
}
dan::Shader *dan::ImgDisp::getShader() {
    return shader;
}

void dan::ImgDisp::setup(Context &c) {
    if (shader != nullptr) {
        c.setShader(*shader);
    }
    texture->bind();
}

void dan::ImgDisp::render(Context &c) {
    texture->render(c);
}
