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
    /**
     * A group of hibotxes.
     * There are only two types of hitboxes:
     * The basic yet efficient circles,
     * and the advanced yet expensive polygons.
     * */
    class Group {
    public:
        /// An entity
        typedef std::shared_ptr<Entity> entity_t;
        /// The oupput of a collsion test
        typedef std::vector<std::pair<entity_t, entity_t>> output_t;
        /// The circle hitbox type
        typedef std::pair<entity_t, Circle> circle_t;
        /// The polygon hitbox type
        typedef std::pair<entity_t, Polygon> polygon_t;
        /// A vector of circles
        typedef std::vector<circle_t> circles_t;
        /// A vector of polygons
        typedef std::vector<polygon_t> polygons_t;
    private:
        /// The circle hitboxes
        circles_t circles;
        /// The polygon hitboxes
        polygons_t polygons;
        /// If false, the hitbox should sync information
        /// from the entities to the hitboxes
        bool valid;
        /**
         * Sync data from the entitys to the hitboxes
         * */
        void doUpdate();
    public:
        /**
         * An empty group
         * */
        Group();
        /**
         * Add a circle with a entity owner
         * \param owner The entity
         * */
        void pushCircle(const entity_t &owner);
        /** Add a polygon with an entity owner
         * \param owner The owner
         * \param points The polygon points
         * */
        void pushPolygon(const entity_t &owner, const Polygon::points_t &points);
        /**
         *  Remove all hitboxes owned by the given entity
         * \param ptr The entity
         * \return true if any were removed
         * */
        bool erase(Entity *ptr);
        /**
         * Delete all content
         * */
        void clear();
        /**
         * If !valid, doUpdate()
         * */
        void update();
        /**
         * Sets valid to false, triggering
         * a call to doUpdate later on
         * */
        void invalidate();
        /**
         * Test two group's hitboxes against each-other
         * \param other The other group
         * \param output Place to store collision pairs
         * */
        void test(Group &other, output_t &output);
    };
}

#endif
