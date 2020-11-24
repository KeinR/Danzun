#ifndef DANZUN_RECTANGLE_H_INCLUDED
#define DANZUN_RECTANGLE_H_INCLUDED

#include "Hitbox.h"

// An optimized Polygon that takes a definate number of vertices (4)
// And does not do rotations

namespace dan {
    class Rectangle: public Hitbox {
        float x;
        float y;
        // Half width/height as x/y refer to the center
        float width;
        float height;
    public:
        Rectangle(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f);
        void setWidth(float w);
        void setHeight(float h);
        float getWidth();
        float getHeight();

        float getMinX() const override;
        float getMinY() const override;
        float getMaxX() const override;
        float getMaxY() const override;
        void setX(float x) override;
        void setY(float y) override;
        void setRotation(float radians) override;
        // Apply position and rotation
        void load() override;
        bool intersects(const Circle &hb) const override;
    };
}

#endif
