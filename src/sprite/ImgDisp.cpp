#include "ImgDisp.h"

#include "../core/Context.h"

dan::ImgDisp::ImgDisp(const texture_t &texture, const shader_t &shader):
    texture(texture), shader(shader)
{
}
void dan::ImgDisp::setTexture(const texture_t &texture) {
    this->texture = texture;
}
void dan::ImgDisp::setShader(const shader_t &shader) {
    this->shader = shader;
}
dan::ImgDisp::texture_t &dan::ImgDisp::getTexture() {
    return texture;
}
dan::ImgDisp::shader_t &dan::ImgDisp::getShader() {
    return shader;
}

void dan::ImgDisp::setup(Context &c) {
    if (shader) {
        c.setShader(shader);
    }
}

void dan::ImgDisp::render(Context &c) {
    texture->bind();
    texture->render(c);
}
