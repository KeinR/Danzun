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
    public:
        Polygon();
        points_t &getPoints();
        void setPoints(const std::vector<float> &p);
        void loadLines();
        bool intersects(Circle &c) override;
    };
}

#endif
