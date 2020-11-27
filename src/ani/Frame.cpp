#include "Frame.h"

#include "../core/Context.h"

dan::Frame::Frame(const texture_t &texture, float length, Shader *shader):
    texture(texture), length(length), shader(shader) {
}
float dan::Frame::getLength() const {
    return length;
}
void dan::Frame::setup(Context &c) {
    if (shader != nullptr) {
        c.setShader(*shader);
    }
    texture->bind();
}
void dan::Frame::render(Context &c) {
    texture->render(c);
}
