#ifndef DANZUN_WINDOWEVENT_H_INCLUDED
#define DANZUN_WINDOWEVENT_H_INCLUDED

#include "Events.h"

namespace dan {
    class KeyMods;
}

namespace dan {
    class WindowEvent {
    public:
        virtual ~WindowEvent() = 0;
        virtual void keyPressed(const event::KeyPress &e);
        virtual void mouseMoved(const event::MouseMove &e);
        virtual void mouseClicked(const event::MouseClick &e);
        virtual void mouseScrolled(const event::MouseScroll &e);
        virtual void charInput(const event::CharInput &e);
    };
}

#endif
