#include "Group.h"

dan::Group::Group() {
}
void dan::Group::pushCircle(const circle &v) {
    circles.push_back(v);
}
void dan::Group::pushRect(const rectangle &v) {
    rectangles.push_back(v);
}
void dan::Group::pushPolygon(const polygon &v) {
    polygons.push_back(v);
}
void dan::Group::clear() {
    circles.clear();
    rectangles.clear();
    polygons.clear();
}
void dan::Group::test(Group &other, std::vector<std::pair<int,int>> &output) {
    // TODO: Add code to hitboxes to allow them to test each-other
    for (circle c : other.circles) {
        for (circle c1 : circles) {
            if (c1.interects(c)) {
                output.emplace_back(c1.id, c.id);
            }
        }
        for (rectangle r : rectangles) {
            if (r.interects(c)) {
                output.emplace_back(r.id, c.id);
            }
        }
        for (polygon p : polygons) {
            if (p.interects(c)) {
                output.emplace_back(p.id, c.id);
            }
        }
    }
}