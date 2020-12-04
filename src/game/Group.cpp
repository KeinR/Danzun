#include "Group.h"

dan::Group::Group() {
}
void dan::Group::pushCircle(const circle &v) {
    circles.push_back(v);
}
void dan::Group::pushPolygon(const polygon &v) {
    polygons.push_back(v);
}
void dan::Group::clear() {
    circles.clear();
    polygons.clear();
}
void dan::Group::test(Group &other, std::vector<std::pair<int,int>> &output) {
    // TODO: Add code to hitboxes to allow them to test each-other
    for (circle &c : other.circles) {
        for (circle &c1 : circles) {
            if (c1.hitbox.intersects(c.hitbox)) {
                output.emplace_back(c1.id, c.id);
            }
        }
        for (polygon &p : polygons) {
            if (p.hitbox.intersects(c.hitbox)) {
                output.emplace_back(p.id, c.id);
            }
        }
    }
    for (polygon &c : other.polygons) {
        for (circle &c1 : circles) {
            if (c1.hitbox.intersects(c.hitbox)) {
                output.emplace_back(c1.id, c.id);
            }
        }
        for (polygon &p : polygons) {
            if (p.hitbox.intersects(c.hitbox)) {
                output.emplace_back(p.id, c.id);
            }
        }
    }
}
