#ifndef DANZUN_CIRCLE_H_INCLUDED
#define DANZUN_CIRCLE_H_INCLUDED

#include "Hitbox.h"

namespace dan {
    class Polygon;
}

namespace dan {
    class Circle: public Hitbox {
        float x;
        float y;
        float radius;
    public:
        Circle();

        float getRadius() const;
        float getX() const;
        float getY() const;

        void setRadius(float r);
        void setX(float x) override;
        void setY(float y) override;

        float getMinX() const override;
        float getMinY() const override;
        float getMaxX() const override;
        float getMaxY() const override;

        // Does nothing
        void load() override;
        // Does nothing
        void setRotation(float radians) override;
        bool intersects(const Circle &c) const override;
        bool intersects(const Polygon &p) const;
    };
}

#endif
