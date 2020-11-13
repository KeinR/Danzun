#include "Sprite.h"

#include "../core/Context.h"
#include "../core/debug.h"

dan::Sprite::Sprite() {
}
void dan::Sprite::setConf(const conf_t &cf) {
    conf = cf;
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
void dan::Sprite::setCenterX(float x) {
    mat.x = x - mat.width / 2;
}
void dan::Sprite::setCenterY(float y) {
    mat.y = y - mat.height / 2;
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

void dan::Sprite::render(Context &c) {
    DANZUN_ASSERT(conf);
    conf->setup(c);
    mat.load(c);
    conf->render(c);
}
