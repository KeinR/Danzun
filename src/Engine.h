#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include "win/Window.h"
#include "win/WindowEvent.h"
#include "core/Context.h"
#include "game/Game.h"
#include "Target.h"

namespace dan {
    class Group;
}

namespace dan {
    class Engine: private WindowEvent {
        Window window;
        Context rc;
        Node *scene;

        Game game;
        Target gameTarget;
    public:
        Engine();
        void setScene(Node &s);
        void setGameSize(int w, int h);
        void renderGameTarget();
        void bindGameTexture();
        void run();
    };
}

#endif

