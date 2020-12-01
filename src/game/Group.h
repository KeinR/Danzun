#ifndef DANZUN_GROUP_H_INCLUDED
#define DANZUN_GROUP_H_INCLUDED

#include <vector>
#include <utility>

#include "../math/Circle.h"
#include "../math/Rectangle.h"
#include "../math/Polygon.h"

namespace dan {
    class Group {
    public:
        struct circle {
            int id;
            Circle hitbox;
        };
        struct rectangle {
            int id;
            Rectangle hitbox;
        };
        struct polygon {
            int id;
            Polygon hitbox;
        };
    private:
        std::vector<circle> circles;
        std::vector<rectangle> rectangles;
        std::vector<polygon> polygons;
    public:
        Group();
        void pushCircle(const circle &v);
        void pushRect(const rectangle &v);
        void pushPolygon(const polygon &v);
        void clear();
        void test(Group &other, std::vector<std::pair<int,int>> &output);
    };
}

#endif
