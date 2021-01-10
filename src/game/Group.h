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
        typedef std::shared_ptr<Entity> entity_t;
        typedef std::vector<std::pair<entity_t, entity_t>> output_t;
        typedef std::pair<entity_t, Circle> circle_t;
        typedef std::pair<entity_t, Polygon> polygon_t;
        typedef std::vector<circle_t> circles_t;
        typedef std::vector<polygon_t> polygons_t;
    private:
        circles_t circles;
        polygons_t polygons;
        bool valid;
        void doUpdate();
    public:
        Group();
        void pushCircle(const entity_t &owner);
        void pushPolygon(const entity_t &owner, const Polygon::points_t &points);
        bool erase(Entity *ptr);
        void clear();
        void update();
		void invalidate();
        void test(Group &other, output_t &output);
    };
}

#endif
