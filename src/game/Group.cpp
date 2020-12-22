#include "Group.h"

#include "Entity.h"

dan::Group::Group() {
}
void dan::Group::pushCircle(const entity_t &owner) {
    circles.emplace_back(owner, Circle());
}
void dan::Group::pushPolygon(const entity_t &owner) {
    polygons.emplace_back(owner, Polygon());
}
bool dan::Group::erase(Entity *ptr) {
    for (circles_t::iterator it = circles.begin(); it < circles.end(); ++it) {
        if (it->first.lock().get() == ptr) {
            circles.erase(it);
            return true;
        }
    }
    for (polygons_t::iterator it = polygons.begin(); it < polygons.end(); ++it) {
        if (it->first.lock().get() == ptr) {
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

    for (circles_t::iterator it = circles.begin(); it < circles.end();) {
        entityLock_t e = it->first.lock();
        if (e) {
            it->second.setX(e->getX());
            it->second.setY(e->getY());
            it->second.setRadius(std::min(e->getWidth(), e->getHeight()) / 2);
            ++it;
        } else {
            it = circles.erase(it);
        }
    }
    for (polygons_t::iterator it = polygons.begin(); it < polygons.end();) {
        entityLock_t e = it->first.lock();
        if (e) {
            it->second.setX(e->getX());
            it->second.setY(e->getY());
            it->second.setRotation(e->getRotation());
            ++it;
        } else {
            it = polygons.erase(it);
        }
    }
}
void dan::Group::test(Group &other, output_t &output) {

    // Not thread safe: update() results could be outdated 

    for (circle_t &c : other.circles) {
        for (circle_t &c1 : circles) {
            if (c1.second.intersects(c.second)) {
                output.emplace_back(c1.first.lock(), c.first.lock());
            }
        }
        for (polygon_t &p : polygons) {
            if (p.second.intersects(c.second)) {
                output.emplace_back(p.first.lock(), c.first.lock());
            }
        }
    }
    for (polygon_t &c : other.polygons) {
        for (circle_t &c1 : circles) {
            if (c1.second.intersects(c.second)) {
                output.emplace_back(c1.first.lock(), c.first.lock());
            }
        }
        for (polygon_t &p : polygons) {
            if (p.second.intersects(c.second)) {
                output.emplace_back(p.first.lock(), c.first.lock());
            }
        }
    }
}
