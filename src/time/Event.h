#ifndef DANZUN_TASK_H_INCLUDED
#define DANZUN_TASK_H_INCLUDED

#include <functional>

#include "Timer.h"

namespace dan {
    class Clock;
}

namespace dan {
    template<class T = void()>
    class Event {
    public:
        typedef std::function<T> callback_t;
    private:
        callback_t callback;
        Timer timer;
    public:
        Event(const Clock &c);
        Event(const Clock &ck, float s, const callback_t &c, bool autoStart = true);
        void setTask(const callback_t &c);
        void setTime(float s);
        void start();
        template<class... Args>
        void poll(Args&&... args);
    };
}

#include "Event.inl"

#endif
