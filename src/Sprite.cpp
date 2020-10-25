#include "Sprite.h"

dan::Sprite::Sprite(): width(100), height(100) {
}
void dan::Sprite::setTexture(const texture_t &tex) {
    texture = tex;
}
void dan::Sprite::setWidth(int w) {
    width = w;
}
void dan::Sprite::setHeight(int h) {
    height = h;
}
