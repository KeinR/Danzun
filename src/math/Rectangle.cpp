#include "Rectangle.h"

#include "Line.h"

dan::Rectangle::Rectangle(float x, float y, float width, float height):
    x(x), y(y), width(width), height(height)
{
}
void dan::Rectangle::setWidth(float w) {
    width = w / 2.0f;
}
void dan::Rectangle::setHeight(float h) {
    height = h / 2.0f;
}
float dan::Rectangle::getWidth() {
    return width * 2.0f;
}
float dan::Rectangle::getHeight() {
    return height * 2.0f;
}

float dan::Rectangle::getMinX() const {
    return x - width;
}
float dan::Rectangle::getMinY() const {
    return y - height;
}
float dan::Rectangle::getMaxX() const {
    return x + width;
}
float dan::Rectangle::getMaxY() const {
    return y + height;
}
void dan::Rectangle::setX(float x) {
    this->x = x;
}
void dan::Rectangle::setY(float y) {
    this->y = y;
}
void dan::Rectangle::setRotation(float radians) {
    // Rotation disabled for optimization
}
void dan::Rectangle::load() {
    // Nothing to be done
}
bool dan::Rectangle::intersects(const Circle &hb) const {
    // Temporary sitation, obvious room to optimize
    Line lines[4];
    lines[0] = Line(getMinX(), getMinY(), getMaxX(), getMinY());
    lines[1] = Line(getMinX(), getMinY(), getMinX(), getMaxY());
    lines[2] = Line(getMinX(), getMaxY(), getMaxX(), getMaxY());
    lines[3] = Line(getMaxX(), getMinY(), getMaxX(), getMaxY());

    for (int i = 0; i < 4; i++) {
        if (lines[i].intersects(hb)) {
            return true;
        }
    }
    return false;
}
