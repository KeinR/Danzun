#include "Circle.h"

#include <cmath>

dan::Circle::Circle(): x(0), y(0), radius(10) {
}

float dan::Circle::getRadius() const {
    return radius;
}
float dan::Circle::getX() const {
    return x;
}
float dan::Circle::getY() const {
    return y;
}

void dan::Circle::setRadius(float r) {
    radius = r;
}
void dan::Circle::setX(float x) {
    this->x = x;
}
void dan::Circle::setY(float y) {
    this->y = y;
}
void dan::Circle::setRotation(float radians) {
    // Do nothing
}
bool dan::Circle::interescts(Circle &c) {
    return std::hypot(c.getX() - getX(), c.getY() - getY()) <= c.getRadius() + getRadius();
}
