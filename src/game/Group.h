#ifndef DANZUN_GROUP_H_INCLUDED
#define DANZUN_GROUP_H_INCLUDED

#include <vector>
#include <utility>
#include <memory>

#include <sol/sol.hpp>

#include "../math/Circle.h"
#include "../math/Polygon.h"

namespace dan {
    class Entity;
}

namespace dan {
    class Group {
    public:
        typedef std::weak_ptr<Entity> entity_t;
        typedef std::shared_ptr<Entity> entityLock_t;
        typedef std::vector<std::pair<entityLock_t, entityLock_t>> output_t;
        typedef std::pair<entity_t, Circle> circle_t;
        typedef std::pair<entity_t, Polygon> polygon_t;
        typedef std::vector<circle_t> circles_t;
        typedef std::vector<polygon_t> polygons_t;
    private:
        circles_t circles;
        polygons_t polygons;
    public:
        Group();
        void pushCircle(const entity_t &owner);
        void pushPolygon(const entity_t &owner);
        bool erase(Entity *ptr);
        void clear();
        void update();
        void test(Group &other, output_t &output);
    };
}

#endif
