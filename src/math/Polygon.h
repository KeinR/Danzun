#ifndef DANZUN_POLYGON_H_INCLUDED
#define DANZUN_POLYGON_H_INCLUDED

#include <vector>

#include "Hitbox.h"
#include "Line.h"

namespace dan {
    class Polygon: public Hitbox {
    public:
        typedef std::vector<float> points_t;
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
        void transX(float c, float s, float x, float y);
        void transY(float c, float s, float x, float y);
    public:
        Polygon();
        points_t &getPoints();
        void setPoints(const std::vector<float> &p);

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
        bool intersects(Circle &c) const override;
    };
}

#endif
