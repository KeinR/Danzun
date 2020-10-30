#ifndef DANZUN_EVENTCALLBACK_H_INCLUDED
#define DANZUN_EVENTCALLBACK_H_INCLUDED

namespace dan {
    class Engine;
}

namespace dan {
    class EventCallback {
    public:
        virtual ~EventCallback() = 0;
        virtual void onFrame(Engine &e, float deltaTime);
    };
}

#endif
