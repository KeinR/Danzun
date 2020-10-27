#ifndef DANZUN_LINE_H_INCLUDED
#define DANZUN_LINE_H_INCLUDED

namespace dan {
    class Circle;
}

namespace dan {
    template<typename T>
    class LineTemplate {
        T m;
        T b;
        T domainMin;
        T domainMax;
        T rangeMin;
        T rangeMax;
    public:
        Line();
        Line(T x0, T y0, T x1, T y1);

        void setM(T m);
        void setB(T b);
        void setDomainMin(T x);
        void setDomainMax(T x);
        void setRangeMin(T y);
        void setRangeMax(T y);

        void setPoints(T x0, T y0, T x1, T y1);

        bool inDomain(T x) const;
        bool inRange(T y) const;

        // Vertical line: x = domainMin / x = domainMax
        bool isVertical() const;

        bool intersects(const Circle &c) const;

        // Result is quiet NAN if line is vertical 
        T solveForY(T x) const;
    };

    typedef LineTemplate<float> Line;
}

#endif
