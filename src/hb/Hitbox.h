#ifndef DANZUN_HB_HITBOX_H_INCLUDED
#define DANZUN_HB_HITBOX_H_INCLUDED

namespace dan::hb {
    class Circle;
}

namespace dan::hb {
    class Hitbox {
    public:
        virtual ~Hitbox() = 0;
        virtual void setX(float x) = 0;
        virtual void setY(float y) = 0;
        virtual void setRotation(float radians) = 0;
        virtual bool intersects(Circle &hb) = 0;
    };
}

#endif
