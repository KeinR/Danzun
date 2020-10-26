#include "Circle.h"

#include <cmath>

dan::hb::Circle::Circle(): x(0), y(0), radius(10) {
}

float dan::hb::Circle::getRadius() {
    return radius;
}
float dan::hb::Circle::getX() {
    return x;
}
float dan::hb::Circle::getY() {
    return y;
}

void dan::hb::Circle::setRadius(float r) {
    radius = r;
}
void dan::hb::Circle::setX(float x) {
    this->x = x;
}
void dan::hb::Circle::setY(float y) {
    this->y = y;
}
void dan::hb::Circle::setRotation(float radians) {
    // Do nothing
}
bool dan::hb::Circle::interescts(Circle &c) {
    return std::hypot(c.getX() - getX(), c.getY() - getY()) <= c.getRadius() + getRadius();
}
