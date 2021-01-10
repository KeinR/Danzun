#ifndef DANZUN_API_ENGINE_H_INCLUDED
#define DANZUN_API_ENGINE_H_INCLUDED

#include <sol/forward.hpp>

namespace dan {
    class Engine;
}

namespace dan::api {
    /**
     * Interface to the master engine class
     * */
    class Engine {
        /// Handle to the engine
        /// This can be a pointer as the
        /// lua state is wrapped in the engine.
        ::dan::Engine *handle;
    public:
        /**
         * Construct with an engine
         * \param handle The engine
         * */
        Engine(::dan::Engine &handle);

        /**
         * Gets underlying handle
         * \return The handle
         * */
        ::dan::Engine *getHandle();
        /**
         * Terminate the program.
         * Effectively calls exit(status), so this is
         * a bad idea!
         * */
        void term(int status);
        /**
         * Sets the Frames Per Second cap
         * \param value The new cap
         * */
        void setMaxFPS(float value);
        /**
         * Toggles Vertical Synchronization
         * \param value true of on
         * */
        void toggleVSync(bool value);

        /**
         * Never throw errors
         * */
        void setThrowNever();
        /**
         * Only throw errors when it's serious
         * */
        void setThrowSevere();
        /**
         * Throw errors when anything bad happens
         * */
        void setThrowAll();

        /**
         * Gets the Frames Pre Second cap
         * \return The cap
         * */
        float getMaxFPS();
        /**
         * Sets the active texture.
         * Note: this is implemented with glActiveTexture(GL_TEXTURE0 + value)
         * \param l The current state
         * \param value The active texture. Should be kept to what is supported
         *              (you should do your own reaserch, but often the cap is 48)
         * */
        void setActiveTexture(sol::this_state l, unsigned int value);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
