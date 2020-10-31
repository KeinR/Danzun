#include "Sprite.h"

#include "core/Context.h"

dan::Sprite::Sprite() {
}
void dan::Sprite::setTexture(const texture_t &tex) {
    texture = tex;
}
void dan::Sprite::setWidth(float w) {
    mat.width = w;
}
void dan::Sprite::setHeight(float h) {
    mat.height = h;
}
void dan::Sprite::setX(float x) {
    mat.x = x;
}
void dan::Sprite::setY(float y) {
    mat.y = y;
}
void dan::Sprite::setRotation(float r) {
    mat.rotation = r;
}

int dan::Sprite::getWidth() const {
    return mat.width;
}
int dan::Sprite::getHeight() const {
    return mat.height;
}
int dan::Sprite::getX() const {
    return mat.x;
}
int dan::Sprite::getY() const {
    return mat.y;
}
float dan::Sprite::getRotation() const {
    return mat.rotation;
}


void dan::Sprite::setShader(const shader_t &s) {
    shader = s;
}

void dan::Sprite::render(Context &c) {
    if (shader) {
        c.setShader(shader);
    }
    mat.load(c);
    texture->render(c);
}
