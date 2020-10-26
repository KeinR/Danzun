#include "Polygon.h"

#include <cmath>

#include "Circle.h"

dan::Polygon::Polygon() {
}
dan::Polygon::points_t &dan::Polygon::getPoints() {
    return points;
}
void dan::Polygon::setPoints(const std::vector<float> &p) {
    points = p;
}
void dan::Polygon::loadLines() {
    typedef points_t::size_type size;
    // No. points must be even
    size end = points.size() - points.size() % 2;
    // Number of lines equal to that of the number of points.
    // Points are in pairs of 2 (x/y)
    lines.clear();
    lines.reserve(end / 2);
    for (size i = 0; i < end; i += 2) {
        size next = (i + 2) % end;
        lines.emplace_back(
            points[i], points[i+1],
            points[next], points[next+1]
        );
    }
}
bool dan::Polygon::intersects(Circle &c) {
    for (Line &l : lines) {
        if (l.intersects(c)) {
            return true;
        }
    }
    return false;
}
