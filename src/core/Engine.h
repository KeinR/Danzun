#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include <unordered_map>
#include <string>

#include "Context.h"
#include "../win/Window.h"
#include "../win/WindowEvent.h"
#include "../game/Game.h"
#include "../render/Target.h"

namespace dan {
    class Group;
    class EventCallback;
}

namespace dan {
    class Engine: private WindowEvent {
        Window window;
        Context rc;
        Node *scene;
        WindowEvent *windowEventCallback;
        EventCallback *eventCallback;

        Game game;
        Target gameTarget;
        bool gameActive;
        float gameSpeed;

        bool callbackCallable();
    public:
        Engine(const std::string &winName, int width, int height);

        void keyPressed(const event::KeyPress &e) override;
        void mouseMoved(const event::MouseMove &e) override;
        void mouseClicked(const event::MouseClick &e) override;
        void mouseScrolled(const event::MouseScroll &e) override;
        void charInput(const event::CharInput &e) override;

        // Set `nullptr` for NONE (default)
        void setWindowEventCallback(WindowEvent *e);
        // Set `nullptr` for NONE (default)
        void setEventCallback(EventCallback *e);

        Window &getWindow();
        Game &getGame();

        void setGameActive(bool flag);
        bool isGameActive() const;

        void setGameSpeed(float s);
        float getGameSpeed() const;

        void setRefreshRate(int count);

        Context &getContext();
        void setScene(Node &s);
        void setGameSize(int w, int h);
        void renderGameTarget();
        void bindGameTexture();
        void run();
    };
}

#endif

