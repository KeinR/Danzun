#include "Frame.h"

#include "core/Context.h"

dan::Frame::Frame(const texture_t &texture, float length, const shader_t &shader):
    texture(texture), length(length), shader(shader) {
}
float dan::Frame::getLength() const {
    return length;
}
void dan::Frame::setup(Context &c) {
    if (shader) {
        c.setShader(shader);
    }
}
void dan::Frame::render(Context &c) {
    texture->render(c);
}
