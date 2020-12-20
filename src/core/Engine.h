#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include <unordered_map>
#include <filesystem>

#include <sol/sol.hpp>

#include "Data.h"
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
        Data data;

        WindowEvent *windowEventCallback;
        EventCallback *eventCallback;

        sol::state s;

        Game game;
        bool gameActive;
        float gameSpeed;

        // Cautious call - don't call if nil
        void cCall(const std::string &functionGlobalName);
        bool callbackCallable();
    public:
        Engine();

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
        Data &getData();
        sol::state_view getState();

        void setGameActive(bool flag);
        bool isGameActive() const;

        void setGameSpeed(float s);
        float getGameSpeed() const;

        Context &getContext();

        void open(const std::filesystem::path &filePath);
        void run();

        void start(const std::filesystem::path &filePath);

        static Engine &fromLua(sol::state_view lua);
    };
}

#endif

