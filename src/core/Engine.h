#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include <string>
#include <functional>
#include <filesystem>
#include <mutex>
#include <atomic>

#include <sol/sol.hpp>

#include "Context.h"
#include "../win/Window.h"
#include "../win/WindowEvent.h"
#include "../game/Game.h"
#include "../audio/Device.h"
#include "../audio/Context.h"

namespace dan {
    class Group;
    class EventCallback;
}

namespace dan {
    class Engine: private WindowEvent {

        Window window;

        Context rc;

        audio::Device audioDevice;
        audio::Context audioContext;

        sol::state s;

        Game game;

        float maxFPS;
        float frameInterval;

        bool threading;
        std::recursive_mutex ctxLock;
        std::atomic<int> lockCount;

        // Cautious call - don't call if nil
        void cCall(const std::string &functionGlobalName);
        bool callbackCallable();
        void setupState();
        void run(const std::string &functionName, const std::string &loopDebugName, const std::function<bool()> &predicate);
    public:
        Engine();

        // For other threads accessing OpenGL functions
        void lockContext();
        void unlockContext();

        void keyPressed(const event::KeyPress &e) override;
        void mouseMoved(const event::MouseMove &e) override;
        void mouseClicked(const event::MouseClick &e) override;
        void mouseScrolled(const event::MouseScroll &e) override;
        void charInput(const event::CharInput &e) override;

        Window &getWindow();
        Game &getGame();
        sol::state_view getState();

        Context &getContext();

        void setMaxFPS(float value);
        float getMaxFPS();

        void open(const std::filesystem::path &filePath);

        void start(const std::filesystem::path &filePath);

        static Engine &fromLua(sol::state_view lua);
    };
}

#endif

