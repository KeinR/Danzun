#ifndef DANZUN_HITBOX_H_INCLUDED
#define DANZUN_HITBOX_H_INCLUDED

namespace dan {
    class Circle;
}

namespace dan {
    class Hitbox {
    public:
        virtual ~Hitbox() = 0;
        virtual float getMinX() const = 0;
        virtual float getMinY() const = 0;
        virtual float getMaxX() const = 0;
        virtual float getMaxY() const = 0;
        virtual void setX(float x) = 0;
        virtual void setY(float y) = 0;
        virtual void setRotation(float radians) = 0;
        // Apply position and rotation
        virtual void load() = 0;
        virtual bool intersects(const Circle &hb) const = 0;
    };
}

#endif
