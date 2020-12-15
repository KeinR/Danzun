#include "Group.h"

#include "Entity.h"

dan::Group::Group() {
}
void dan::Group::pushCircle(Entity &owner) {
    circles.emplace_back(&owner, Circle());
}
void dan::Group::pushPolygon(Entity &owner) {
    polygons.emplace_back(&owner, Polygon());
}
bool dan::Group::erase(Entity *ptr) {
    for (std::vector<circle_t>::iterator it = circles.begin(); it < circles.end(); ++it) {
        if (it->first == ptr) {
            circles.erase(it);
            return true;
        }
    }
    for (std::vector<polygon_t>::iterator it = polygons.begin(); it < polygons.end(); ++it) {
        if (it->first == ptr) {
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
    // TODO: Seperation of sprite and hitbox
    for (circle_t &c : circles) {
        c.second.setX(c.first->getX());
        c.second.setY(c.first->getY());
        c.second.setRadius(std::min(c.first->getWidth(), c.first->getHeight()) / 2);
    }
    for (polygon_t &c : polygons) {
        c.second.setX(c.first->getX());
        c.second.setY(c.first->getY());
        c.second.setRotation(c.first->getRotation());
    }
}
void dan::Group::test(Group &other, std::vector<std::pair<Entity*, Entity*>> &output) {

    for (circle_t &c : other.circles) {
        for (circle_t &c1 : circles) {
            if (c1.second.intersects(c.second)) {
                output.emplace_back(c1.first, c.first);
            }
        }
        for (polygon_t &p : polygons) {
            if (p.second.intersects(c.second)) {
                output.emplace_back(p.first, c.first);
            }
        }
    }
    for (polygon_t &c : other.polygons) {
        for (circle_t &c1 : circles) {
            if (c1.second.intersects(c.second)) {
                output.emplace_back(c1.first, c.first);
            }
        }
        for (polygon_t &p : polygons) {
            if (p.second.intersects(c.second)) {
                output.emplace_back(p.first, c.first);
            }
        }
    }
}
