#include "Polygon.h"

#include <cmath>

#include "Circle.h"

dan::Polygon::Polygon():
    minX(0), minY(0),
    maxX(0), maxY(0),
    centerX(0), centerY(0),
    x(0), y(0),
    rotation(0)
{
}
dan::Polygon::points_t &dan::Polygon::getPoints() {
    return points;
}
void dan::Polygon::setPoints(const std::vector<float> &p) {
    points = p;
}

void dan::Polygon::setCenterX(float x) {
    centerX = x;
}
void dan::Polygon::setCenterY(float y) {
    centerY = y;
}
void dan::Polygon::detectCenter() {
    setCenterX((minX + maxX) / 2.0f);
    setCenterY((minY + maxY) / 2.0f);
}

float dan::Polygon::getMinX() {
    return minX;
}
float dan::Polygon::getMinY() {
    return minY;
}
float dan::Polygon::getMaxX() {
    return maxX;
}
float dan::Polygon::getMaxY() {
    return maxY;
}

void dan::Polygon::transX(float c, float s, float x, float y) {
    return centerX + (x - centerX) * c - (y - centerY) * s + this->x;
}
void dan::Polygon::transY(float c, float s, float x, float y) {
    return centerY + (x - centerX) * s + (y - centerY) * c + this->y;
}

void dan::Polygon::load() {
    // Requres there's at least one point
    // for starting min/max
    if (points.size() < 2) {
        return;
    }

    typedef points_t::size_type size;
    // No. points must be even
    size end = points.size() - points.size() % 2;
    // Number of lines equal to that of the number of points.
    // Points are in pairs of 2 (x/y)
    lines.clear();
    lines.reserve(end / 2);

    minX = points[0];
    maxX = points[0];
    minY = points[1];
    maxY = points[1];

    const float c = std::cos(rotation);
    const float s = std::sin(rotation);
    for (size i = 0; i < end; i += 2) {
        size next = (i + 2) % end;
        float x0 = points[i];
        float y0 = points[i+1];
        float x1 = points[next];
        float y1 = points[next+1];
        lines.emplace_back(
            transX(c, s, x0, y0), transY(c, s, x0, y0),
            transX(c, s, x1, y1), transY(c, s, x1, y1)
        );
        if (x0 < minX) {
            minX = x0;
        } else if (x0 > maxX) {
            maxX = x0;
        }
        if (y0 < minY) {
            minY = y0;
        } else if (y0 > maxY) {
            maxY = y0;
        }
    }
}

void dan::Polygon::setX(float x) {
    this->x = x;
}
void dan::Polygon::setY(float y) {
    this->y = y;
}
void dan::Polygon::setRotation(float radians) {
    this->rotation = radians;
}

bool dan::Polygon::intersects(Circle &c) {
    for (Line &l : lines) {
        if (l.intersects(c)) {
            return true;
        }
    }
    return false;
}
