#ifndef DANZUN_POLYGON_H_INCLUDED
#define DANZUN_POLYGON_H_INCLUDED

#include <vector>

#include "Line.h"

namespace dan {
    class Circle;
}

namespace dan {
    /**
     * A simple polygon
     * */
    class Polygon {
    public:
        /**
         * A single raw point
         * */
        struct Point {
            float x;
            float y;
            Point();
            Point(float x, float y);
        };
        /// The points (raw)
        typedef std::vector<Point> points_t;
        /// The lines (compiled)
        typedef std::vector<Line> lines_t;
    private:
        /// The points (raw) 
        points_t points;
        /// The points (translated)
        points_t compPoints;
        /// The lines (compiled)
        /// Are what are actually used in calculations
        lines_t lines;
        /// Width/height 
        float scaleX;
        float scaleY;
        /// Rotation pivot, in translated coordinates
        float pivotX;
        float pivotY;
        /// x/y translation
        float x;
        float y;
        /// In radians
        float rotation;
    public:
        /**
         * Construct an empty polygon
         * */
        Polygon();

        /**
         * \return The raw points this polygon is comprised of
         * */
        points_t &getPoints();
        /**
         * Set the raw poitns
         * \param p The points
         * \note POints must be in the range -1 <= x <= 1 && -1 <= y <= 1
         * */
        void setPoints(const points_t &p);

        /**
         * Set the width of the polygon
         * \param w The width
         * */
        void setWidth(float w);
        /**
         * Set the height of the polygon
         * \param h The height
         * */
        void setHeight(float h);
        /**
         * Set the pivot x of the polygon, relative to the x pos
         * \param x The value
         * */
        void setPivotX(float x);
        /**
         * Set the pivot y of the polygon, relative to the y pos
         * \param y The value
         * */
        void setPivotY(float y);
        /**
         * Set the x pos
         * \param x The value
         * */
        void setX(float x);
        /**
         * Set the y pos
         * \param y The value
         * */
        void setY(float y);
        /**
         * Set the rotation of the polygon
         * \param radians The rotation, in (you guessed it) radians
         * */
        void setRotation(float radians);

        /**
         * Compile the points to lines and translated points.
         * Necessary to sync any changes to the polygon that were made
         * */
        void load();

        /**
         * Test if a point is contained within
         * \param p The point
         * \return true if yes
         * */
        bool hasPoint(const Point &p) const;
        /**
         * Test if it intersects a circle
         * \param c The circle
         * \return true if yes
         * */
        bool intersects(const Circle &c) const;
        /**
         * Test if it intersects a polygon
         * \param p The polygon
         * \return true if yes
         * */
        bool intersects(const Polygon &p) const;
    };
}

#endif
