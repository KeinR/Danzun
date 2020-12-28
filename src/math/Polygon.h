#ifndef DANZUN_POLYGON_H_INCLUDED
#define DANZUN_POLYGON_H_INCLUDED

#include <vector>

#include "Line.h"

namespace dan {
    class Circle;
}

namespace dan {
    class Polygon {
    public:
        struct Point {
            float x;
            float y;
            Point();
            Point(float x, float y);
        };
        typedef std::vector<Point> points_t;
        typedef std::vector<Line> lines_t;
    private:
        // 2D points
        points_t points;
        // Derived from points
        lines_t lines;
        // Point scaling
        float scaleX;
        float scaleY;
        // Pivot of rotation relative to untranslated points.
        float pivotX;
        float pivotY;
        // x/y translation
        float x;
        float y;
        // In radians
        float rotation;
    public:
        Polygon();

        points_t &getPoints();
        // Points must be in NDC, that is -1 <= x <= 1 && -1 <= y <= 1
        void setPoints(const points_t &p);

        void setWidth(float w);
        void setHeight(float h);
        // Pivot values must be in NDC, that is -1 <= x <= 1 && -1 <= y <= 1.
        // They will have their respective scale applied later
        void setPivotX(float x);
        void setPivotY(float y);
        void setX(float x);
        void setY(float y);
        void setRotation(float radians);

        void load();

        bool hasPoint(const Point &p) const;
        bool intersects(const Circle &c) const;
        bool intersects(const Polygon &p) const;
    };
}

#endif
