#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include "WindowEvent.h"

namespace dan {
    class Engine: private WindowEvent {
        Window window;
    public:
        Engine();
    };
}

#endif

