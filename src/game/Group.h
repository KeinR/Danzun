#ifndef DANZUN_GROUP_H_INCLUDED
#define DANZUN_GROUP_H_INCLUDED

#include <vector>
#include <utility>

#include <sol/sol.hpp>

#include "../math/Circle.h"
#include "../math/Polygon.h"

namespace dan {
    class Group {
    public:
        struct circle {
            sol::table obj;
            Circle hitbox;
        };
        struct polygon {
            sol::table obj;
            Polygon hitbox;
        };
    private:
        std::vector<circle> circles;
        std::vector<polygon> polygons;
    public:
        Group();
        void pushCircle(const circle &v);
        void pushPolygon(const polygon &v);
        void clear();
        void test(Group &other, std::vector<std::pair<sol::table, sol::table>> &output);
    };
}

#endif
