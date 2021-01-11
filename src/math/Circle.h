#ifndef DANZUN_CIRCLE_H_INCLUDED
#define DANZUN_CIRCLE_H_INCLUDED

namespace dan {
    class Polygon;
}

namespace dan {
    /**
     * A simple circle.
     * The methods are not worth documenting,
     * however do note that the x/y position is indeed
     * the center if the circle
     * */
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

        bool intersects(const Circle &c) const;
        bool intersects(const Polygon &p) const;
    };
}

#endif
