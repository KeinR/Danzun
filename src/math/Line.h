#ifndef DANZUN_LINE_H_INCLUDED
#define DANZUN_LINE_H_INCLUDED

namespace dan {
    class Circle;
}

namespace dan {
    /**
     * A simple linear equation
     * Not worth documenting extensively
     * */
    template<typename T>
    class LineTpl {
        /// y = mx + b
        // Is NAN if line is vertical
        T m;
        /// y = mx + b
        // Is NAN if line is vertical
        T b;
        T domainMin;
        T domainMax;
        T rangeMin;
        T rangeMax;
    public:
        LineTpl();
        LineTpl(T x0, T y0, T x1, T y1);

        void setM(T m);
        void setB(T b);
        void setDomainMin(T x);
        void setDomainMax(T x);
        void setRangeMin(T y);
        void setRangeMax(T y);

        T getM() const;
        T getB() const;
        T getDomainMin() const;
        T getDomainMax() const;
        T getRangeMin() const;
        T getRangeMax() const;

        void setPoints(T x0, T y0, T x1, T y1);

        bool inDomain(T x) const;
        bool inRange(T y) const;

        /// Vertical line: x = domainMin & x = domainMax
        bool isVertical() const;

        /**
         * Tests if the line crosses the circle
         * \oaran c The circle
         * \return true if yes
         * */
        bool intersects(const Circle &c) const;

        /**
         * y = mx + b
         * */
        T solveForY(T x) const;
    };

    typedef LineTpl<float> Line;
}

#endif
