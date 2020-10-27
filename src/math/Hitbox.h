#ifndef DANZUN_HITBOX_H_INCLUDED
#define DANZUN_HITBOX_H_INCLUDED

namespace dan {
    class Circle;
}

namespace dan {
    class Hitbox {
    public:
        virtual ~Hitbox() = 0;
        virtual float getMinX() = 0;
        virtual float getMinY() = 0;
        virtual float getMaxX() = 0;
        virtual float getMaxY() = 0;
        virtual void setX(float x) = 0;
        virtual void setY(float y) = 0;
        virtual void setRotation(float radians) = 0;
        // Apply position and rotation
        virtual void load() = 0;
        virtual bool intersects(Circle &hb) = 0;
    };
}

#endif
