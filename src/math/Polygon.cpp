#include "Polygon.h"

#include <cmath>

#include "Circle.h"

dan::Point::Point(): Point(0, 0) {
}
dan::Point::Point(float x, float y): x(x), y(y) {
}

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
void dan::Polygon::setPoints(const points_t &p) {
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

float dan::Polygon::getMinX() const {
    return minX;
}
float dan::Polygon::getMinY() const {
    return minY;
}
float dan::Polygon::getMaxX() const {
    return maxX;
}
float dan::Polygon::getMaxY() const {
    return maxY;
}

float dan::Polygon::transX(float c, float s, float x, float y) {
    return centerX + (x - centerX) * c - (y - centerY) * s + this->x;
}
float dan::Polygon::transY(float c, float s, float x, float y) {
    return centerY + (x - centerX) * s + (y - centerY) * c + this->y;
}

void dan::Polygon::load() {
    // Requres there's at least one point
    // for starting min/max
    if (points.size() < 1) {
        return;
    }

    typedef points_t::size_type size;
    // Number of lines equal to that of the number of points.
    lines.clear();
    lines.reserve(points.size());

    minX = points[0].x;
    maxX = points[0].x;
    minY = points[0].y;
    maxY = points[0].y;

    const float c = std::cos(rotation);
    const float s = std::sin(rotation);
    for (size i = 0; i < points.size(); i++) {
        size next = (i + 1) % end;
        float x0 = points[i].x;
        float y0 = points[i].y;
        float x1 = points[next].x;
        float y1 = points[next].y;
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

bool dan::Polygon::intersects(const Circle &c) const {
    for (const Line &l : lines) {
        if (l.intersects(c)) {
            return true;
        }
    }
    return false;
}

bool dan::Polygon::hasPoint(const Point &p) {
    int hits = 0;
    for (int i = 0; i < length; i++) {
        if (lines[i].inDomain(x)) {
            float iy = lines[i].solveForY(p.x, p.y);
            if (iy > p.y) {
                hits++;
            } else if (iy == p.y) {
                return true;
            }
        }
    }
    return hits % 2;
}

bool dan::Polygon::intersects(const Polygon &p) const {
    for (Point &p : p.points) {
        if (this->hasPoint(p)) {
            return true;
        }
    }
    for (Point &p : this->points) {
        if (p.hasPoint(p)) {
            return true;
        }
    }
    return false;
}
