#include "Polygon.h"

#include <cmath>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Circle.h"
#include "../render/Matrix.h"

dan::Polygon::Point::Point(): Point(0, 0) {
}
dan::Polygon::Point::Point(float x, float y): x(x), y(y) {
}

dan::Polygon::Polygon():
    scaleX(0),
    scaleY(0),
    pivotX(0), pivotY(0),
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

void dan::Polygon::setWidth(float w) {
    scaleX = w;
}
void dan::Polygon::setHeight(float h) {
    scaleY = h;
}
void dan::Polygon::setPivotX(float x) {
    pivotX = x;
}
void dan::Polygon::setPivotY(float y) {
    pivotY = y;
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

void dan::Polygon::load() {
    typedef points_t::size_type size;
    // Number of lines equal to that of the number of points.
    lines.clear();
    compPoints.clear();
    lines.reserve(points.size());
    compPoints.reserve(points.size());

    // TODO: Add reflection support
    glm::mat4 model = Matrix(x, y, pivotX, pivotY, scaleX, scaleY, rotation, false).getModel(false);

    for (size i = 0; i < points.size(); i++) {
        glm::vec4 p(points[i].x, points[i].y, 0, 1);
        p = model * p;
        compPoints.emplace_back(p.x, p.y);
    }

    for (size i = 0; i < compPoints.size(); i++) {
        size next = (i + 1) % compPoints.size();
        Point &p1 = compPoints[i];
        Point &p2 = compPoints[next];
        lines.emplace_back(
            p1.x, p1.y,
            p2.x, p2.y
        );
    }
}

bool dan::Polygon::intersects(const Circle &c) const {
    for (const Line &l : lines) {
        if (l.intersects(c)) {
            return true;
        }
    }
    return false;
}

bool dan::Polygon::hasPoint(const Point &p) const {
    int hits = 0;
    for (const Line &l : lines) {
        if (l.inDomain(x)) {
            float iy = l.solveForY(p.x);
            if (iy > p.y || std::isinf(iy)) {
                hits++;
            } else if (iy == p.y) {
                return true;
            }
        }
    }
    return hits % 2;
}

bool dan::Polygon::intersects(const Polygon &pg) const {
    for (const Point &p : pg.compPoints) {
        if (this->hasPoint(p)) {
            return true;
        }
    }
    for (const Point &p : this->compPoints) {
        if (pg.hasPoint(p)) {
            return true;
        }
    }
    return false;
}
