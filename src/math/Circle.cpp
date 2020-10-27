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

float dan::Circle::getMinX() {
    return x - radius;
}
float dan::Circle::getMinY() {
    return y - radius;
}
float dan::Circle::getMaxX() {
    return x + radius;
}
float dan::Circle::getMaxY() {
    return y + radius;
}

void dan::Circle::load() {
    // Do nothing; there's nothing to load...
}

void dan::Circle::setRotation(float radians) {
    // Do nothing
}
bool dan::Circle::interescts(Circle &c) {
    return std::hypot(c.getX() - getX(), c.getY() - getY()) <= c.getRadius() + getRadius();
}
