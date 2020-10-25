#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include "win/Window.h"
#include "win/WindowEvent.h"
#include "core/Context.h"

namespace dan {
    class Engine: private WindowEvent {
        Window window;
        Context rc;
    public:
        Engine();
        void run();
    };
}

#endif

