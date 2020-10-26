#ifndef DANZUN_HB_CIRCLE_H_INCLUDED
#define DANZUN_HB_CIRCLE_H_INCLUDED

#include "Hitbox.h"

#include "../math/Circle.h"

namespace dan::hb {
    class Circle: public math::Circle, public Hitbox {
        float x;
        float y;
        float radius;
    public:
        Circle();

        float getRadius() override;
        float getX() override;
        float getY() override;

        void setRadius(float r);
        void setX(float x) override;
        void setY(float y) override;
        // Does nothing
        void setRotation(float radians) override;
        bool interescts(Circle &c) override;
    };
}

#endif
