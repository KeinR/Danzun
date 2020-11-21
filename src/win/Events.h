#ifndef DANZUN_KEYPRESS_EVENT_H_INCLUDED
#define DANZUN_KEYPRESS_EVENT_H_INCLUDED

#include "enums.h"
#include "KeyMods.h"

namespace dan::event {
    struct KeyPress {
          keyt key;
          keyAction action;
          KeyMods mods;
    };
    struct MouseMove {
        // New x
        double x;
        double y;
    };
    struct MouseClick {
        mouseButton button;
        bool pressed;
        KeyMods mods;
    };
    struct MouseScroll {
        double xOffset;
        double yOffset;
    };
    struct CharInput {
        unsigned int codepoint;
    };
}

#endif
