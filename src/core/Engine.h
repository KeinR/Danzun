#ifndef DANZUN_ENGINE_H_INCLUDED
#define DANZUN_ENGINE_H_INCLUDED

#include <filesystem>
#include <map>

#include <sol/sol.hpp>

#include "Context.h"
#include "../win/Window.h"
#include "../win/enums.h"
#include "../win/WindowEvent.h"
#include "../game/Game.h"
#include "../audio/Device.h"
#include "../audio/Context.h"

namespace dan {
    class Group;
    class EventCallback;
}

namespace dan {
    /**
     * The main driver class
     * */
    class Engine: private WindowEvent {
    public:
        /// Type for key mappings
	typedef std::map<std::string, dan::keyt> keyMappings_t;
    private:
        /// The window
        Window window;

        /// Mappings for name -> enum for keys
	keyMappings_t keyMappings;

        /// The render context
        Context rc;

        /// The audio device
        audio::Device audioDevice;
        /// The audio context
        audio::Context audioContext;

        /// The lua state
        sol::state s;

        /// The game singleton
        Game game;

        /// fps cap
        float maxFPS;
        /// Time to wait between frames
        float frameInterval;

        /**
         * Initialize with a Lua script
         * \param filePath Path to the script
         * */
        void open(const std::filesystem::path &filePath);
        /**
         * Executes the main loop
         * */
        void run();


        /**
         * Calls a given global lua function only if it exists
         * */
        void cCall(const std::string &functionGlobalName);
    public:
        /**
         * Construct an engine
         * \param msaa Number of samples to take when doing multisampling
         * */
        Engine(int msaa);

        /// @{
        /**
         * Key callback (unused)
         * \param e The event object
         * */
        void keyPressed(const event::KeyPress &e) override;
        void mouseMoved(const event::MouseMove &e) override;
        void mouseClicked(const event::MouseClick &e) override;
        void mouseScrolled(const event::MouseScroll &e) override;
        void charInput(const event::CharInput &e) override;
        /// @}

        /**
         * Gets the key mappings
         * */
	keyMappings_t &getKeyMappings();

        /**
         * \return The window
         * */
        Window &getWindow();
        /**
         * \return The game (singleton)
         * */
        Game &getGame();
        /**
         * \return The Lua state
         * */
        sol::state_view getState();

        /**
         * \return The render context
         * */
        Context &getContext();

        /**
         * Sets the FPS cap
         * \param value The new cap
         * */
        void setMaxFPS(float value);
        /**
         * \return the FPS cap
         * */
        float getMaxFPS();

        /**
         * Run the garbage collector for the Lua state
         * */
	void collectGarbage();

        /**
         * Launches from the init file at the given path
         * \param filePath The file
         * */
        void start(const std::filesystem::path &filePath);

        /**
         * Get the engine embedded in the lua state
         * \param lua The state
         * \return The engine
         * */
        static Engine &fromLua(sol::state_view lua);
    };
}

#endif

