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
void dan::Sprite::render(Context &c) {
    mat.load(c);
    texture->render(c);
}
