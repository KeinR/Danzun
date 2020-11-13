#ifndef DANZUN_REALTIMER_H_INLCUDED
#define DANZUN_REALTIMER_H_INLCUDED

#include <chrono>

// Measures real time, as opposed to game time

namespace dan {
    class RealTimer {
        typedef std::chrono::steady_clock clock;
        clock::duration time;
        clock::time_point end;
    public:
        RealTimer();
        RealTimer(unsigned int ms);
        void setTime(unsigned int ms);
        void start();
        bool done();
    };
}

#endif
