#ifndef DANZUN_TIMER_H_INCLUDED
#define DANZUN_TIMER_H_INCLUDED

// Measures game time.
// All units are in seconds.

namespace dan {
    class Clock;
}

namespace dan {
    class Timer {
        Clock *clock;
        float end;
        float duration;
    public:
        Timer(Clock &clock);
        void set(float s);
        void reset();
        bool done() const;
    };
}

#endif
