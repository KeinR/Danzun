#include "Line.h"

#include <cmath>
#include <limits>

#include "Circle.h"

template<typename T>
dan::math::Line<T>::Line(): m(0), b(0), domainMin(0), domainMax(0) {
}

template<typename T>
dan::math::Line<T>::Line(T x0, T y0, T x1, T y1) {
    setPoints(x0, y0, x1, y1);
}

template<typename T>
void dan::math::Line<T>::setM(T m) {
    this->m = m;
}
template<typename T>
void dan::math::Line<T>::setB(T b) {
    this->b = b;
}
template<typename T>
void dan::math::Line<T>::setDomainMin(T x) {
    domainMin = x;
}
template<typename T>
void dan::math::Line<T>::setDomainMax(T x) {
    domainMax = x;
}
template<typename T>
void dan::math::Line<T>::setRangeMin(T y) {
    rangeMin = y;
}
template<typename T>
void dan::math::Line<T>::setRangeMax(T y) {
    rangeMax = y;
}

template<typename T>
void dan::math::Line<T>::setPoints(T x0, T y0, T x1, T y1) {
    T xDiff = x0 - x1;
    if (xDiff == 0) {
        m = std::numeric_limits<T>::quiet_NaN();
        b = std::numeric_limits<T>::quiet_NaN();
        domainMin = x0;
        domainMax = x0;
    } else {
        m = (y0 - y1) / xDiff;
        b = y0 - x0 * m;
        if (x1 > x0) {
            domainMin = x0;
            domainMax = x1;
        } else {
            domainMin = x1;
            domainMax = x0;
        }
    }
    if (y1 > y0) {
        rangeMin = y0;
        rangeMax = y1;
    } else {
        rangeMin = y1;
        rangeMax = y0;
    }
}

template<typename T>
bool dan::math::Line<T>::inDomain(T x) {
    return domainMin <= x && x <= domainMax;
}

template<typename T>
bool dan::math::Line<T>::inRange(T y) {
    return rangeMin <= y && y <= rangeMax;
}

template<typename T>
bool dan::math::Line<T>::isVertical() {
    return m == std::numeric_limits<T>::quiet_NaN();
}

template<typename T>
bool dan::math::Line<T>::intersects(const Circle &c) {
    // i(x) = c(x) - l(x)
    // If l(x) == NaN (undefined), must determine if 
    // c(x) is within the range

    // c(x) = (x - t_x)^2 + (y - t_y)^2 = r^2
    // l(x) = mx + b
    // c(x) = l(x)
    // ...
    // Quatratic formula:
    // a = m^2 + 1
    // b = 2(m(b-t_y)-t_x)
    // c = (b-t_y)^2 - r^2 + t_x^2

    if (isVertical()) {
        float v = std::sqrt(std::pow(c.getRadius(), 2) - std::pow(getDomainMin() - c.getX(), 2));
        float y0 = c.getY() + v;
        float y1 = c.getY() - v;
        if (inRange(y0) || inRange(y1)) {
            return true;
        }
    } else {
        float a = std::pow(getM(), 2) + 1;
        float b = 2 * (getM() * (getB() - c.getY()) - c.getX());
        float c = std::pow(getB() - c.getY(), 2) - std::pow(c.getRadius(), 2) + std::pow(c.getX(), 2);
        float v = std::pow(b, 2) - 4 * a * c;
        if (v >= 0) {
            v = std::sqrt(v);
            float x0 = (-b + v) / (2 * a);
            float x1 = (-b - v) / (2 * a);
            if (inDomain(x0) || inDomain(x1)) {
                return true;
            }
        }
    }

    return false;
}

template<typename T>
T dan::math::Line<T>::solveForY(T x) {
    return x * m + b;
}

template class LineTemplate<float>;
