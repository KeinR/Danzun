#ifndef DANZUN_MATH_CIRCLE_H_INCLUDED
#define DANZUN_MATH_CIRCLE_H_INCLUDED

namespace dan::math {
    class Circle {
    public:
        virtual ~Circle() = 0;
        virtual float getRadius() = 0;
        virtual float getX() = 0;
        virtual float getY() = 0;
    };
}

#endif
