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
        typedef std::pair<Entity*, Circle> circle_t
        typedef std::pair<Entity*, Polygon> polygon_t
    private:
        std::vector<circle_t> circles;
        std::vector<polygon_t> polygons;
    public:
        Group();
        void pushCircle(Entity &owner);
        void pushPolygon(Entity &owner);
        void erase(Entity *ptr);
        void clear();
        void update();
        void test(Group &other, std::vector<std::pair<Entity*, Entity*>> &output);
    };
}

#endif
