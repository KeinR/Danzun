#include "Group.h"

#include "Entity.h"

dan::Group::Group() {
}
void dan::Group::pushCircle(const entity_t &owner) {
    circles.emplace_back(owner, Circle());
}
void dan::Group::pushPolygon(const entity_t &owner, const Polygon::points_t &points) {
    polygons.emplace_back(owner, Polygon());
    polygons.back().second.setPoints(points);
}
bool dan::Group::erase(Entity *ptr) {
    for (circles_t::iterator it = circles.begin(); it < circles.end(); ++it) {
        if (it->first.get() == ptr) {
            circles.erase(it);
            return true;
        }
    }
    for (polygons_t::iterator it = polygons.begin(); it < polygons.end(); ++it) {
        if (it->first.get() == ptr) {
            polygons.erase(it);
            return true;
        }
    }
    return false;
}
void dan::Group::clear() {
    circles.clear();
    polygons.clear();
}
void dan::Group::update() {

    for (circles_t::iterator it = circles.begin(); it < circles.end(); ++it) {
        it->second.setX(it->first->getX());
        it->second.setY(it->first->getY());
        it->second.setRadius(std::min(it->first->getWidth(), it->first->getHeight()) / 2);
    }
    for (polygons_t::iterator it = polygons.begin(); it < polygons.end(); ++it) {
        it->second.setX(it->first->getX());
        it->second.setY(it->first->getY());
        it->second.setRotation(it->first->getRotation());
        it->second.setWidth(it->first->getWidth());
        it->second.setHeight(it->first->getHeight());
        it->second.setPivotX(it->first->getPivotX());
        it->second.setPivotY(it->first->getPivotY());
        it->second.load();
    }
}

void dan::Group::test(Group &other, output_t &output) {

    for (circle_t &c : other.circles) {
        if (c.first->isTangible()) {
            for (circle_t &c1 : circles) {
                if (c1.first->isTangible() && c1.second.intersects(c.second)) {
                    output.emplace_back(c1.first, c.first);
                }
            }
            for (polygon_t &p : polygons) {
                if (p.first->isTangible() && p.second.intersects(c.second)) {
                    output.emplace_back(p.first, c.first);
                }
            }
        }
    }
    for (polygon_t &c : other.polygons) {
        if (c.first->isTangible()) {
            for (circle_t &c1 : circles) {
                if (c1.first->isTangible() && c1.second.intersects(c.second)) {
                    output.emplace_back(c1.first, c.first);
                }
            }
            for (polygon_t &p : polygons) {
                if (p.first->isTangible() && p.second.intersects(c.second)) {
                    output.emplace_back(p.first, c.first);
                }
            }
        }
    }
}
