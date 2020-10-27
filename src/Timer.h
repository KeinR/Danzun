#ifndef DANZUN_TIMER_H_INLCUDED
#define DANZUN_TIMER_H_INLCUDED

#include <chrono>

namespace dan {
    class Timer {
        typedef std::chrono::steady_clock clock;
        clock::duration time;
        clock::time_point end;
    public:
        Timer();
        Timer(unsigned int ms);
        void setTime(unsigned int ms);
        void start();
        bool done();
    };
}

#endif
