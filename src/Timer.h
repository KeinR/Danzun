#ifndef DANZUN_TIMER_H_INCLUDED
#define DANZUN_TIMER_H_INCLUDED

// Measures game time.
// All units are in seconds.

namespace dan {
    class Timer {
        float progress;
        float goal;
    public:
        Timer();
        void advance(float s);
        void set(float duration);
        void reset();
        bool done() const;
    };
}

#endif
