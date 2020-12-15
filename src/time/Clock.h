#ifndef DANZUN_CLOCK_H_INCLUDED
#define DANZUN_CLOCK_H_INCLUDED

namespace dan {
    class Clock {
        // Time measured in seconds
        float time;
        float deltaTime;
    public:
        Clock();
        void setTime(float s);
        void setDeltaTime(float s);
        void pushDeltaTime(float s);
        float &getTimeRef();
        float &getDeltaTimeRef();
        float getTime() const;
        float getDeltaTime() const;
    };
}

#endif
