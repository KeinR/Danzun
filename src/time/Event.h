#ifndef DANZUN_TASK_H_INCLUDED
#define DANZUN_TASK_H_INCLUDED

#include <functional>

#include "Timer.h"

namespace dan {
    class Clock;
}

namespace dan {
    class Event {
    public:
        typedef std::function<void(Event&)> callback_t;
    private:
        callback_t callback;
        Timer timer;
    public:
        Event(const Clock &c);
        Event(const Clock &ck, float s, const callback_t &c, bool autoStart = true);
        void setTask(const callback_t &c);
        void setTime(float s);
        void start();
        void poll();
    };
}

#endif
