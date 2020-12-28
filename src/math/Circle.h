#ifndef DANZUN_CIRCLE_H_INCLUDED
#define DANZUN_CIRCLE_H_INCLUDED

namespace dan {
    class Polygon;
}

namespace dan {
    class Circle {
        float x;
        float y;
        float radius;
    public:
        Circle();

        float getRadius() const;
        float getX() const;
        float getY() const;

        void setRadius(float r);
        void setX(float x);
        void setY(float y);

        float getMinX() const;
        float getMinY() const;
        float getMaxX() const;
        float getMaxY() const;

        // Does nothing
        void load();
        // Does nothing
        void setRotation(float radians);
        bool intersects(const Circle &c) const;
        bool intersects(const Polygon &p) const;
    };
}

#endif
