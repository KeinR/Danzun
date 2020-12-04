#ifndef DANZUN_POLYGON_H_INCLUDED
#define DANZUN_POLYGON_H_INCLUDED

#include <vector>

#include "Hitbox.h"
#include "Line.h"

namespace dan {
    class Circle;
}

namespace dan {
    class Polygon: public Hitbox {
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
        float minX;
        float minY;
        float maxX;
        float maxY;
        // Center of rotation relative to untranslated points.
        float centerX;
        float centerY;
        float x;
        float y;
        // In radians
        float rotation;
        float transX(float c, float s, float x, float y);
        float transY(float c, float s, float x, float y);
    public:
        Polygon();
        points_t &getPoints();
        void setPoints(const points_t &p);

        void setCenterX(float x);
        void setCenterY(float y);
        // Automatically detects center x/y from points
        void detectCenter();

        float getMinX() const override;
        float getMinY() const override;
        float getMaxX() const override;
        float getMaxY() const override;

        void load() override;
        void setX(float x) override;
        void setY(float y) override;
        void setRotation(float radians) override;
        float hasPont(const Point &p) const;
        bool intersects(const Circle &c) const override;
        bool intersects(const Polygon &p) const;
    };
}

#endif
