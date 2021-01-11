#ifndef DANZUN_CONTEXT_H_INCLUDED
#define DANZUN_CONTEXT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

namespace dan {
    class Engine;
    class Shader;
}

namespace dan {
    /**
     * The rendering context
     * Acs as a state manager, and maintains certain metadata.
     * */
    class Context {
        /// The engine
        Engine *engine;
        /// The current shader
        std::shared_ptr<Shader> currentShader;
        /// The viewport width
        int vWidth;
        /// The viewport height
        int vHeight;

    public:
        /**
         * Creates a new context
         * \param e The engine
         * */
        Context(Engine *e);

        /**
         * Binds a shader and keeps a pointer to it if it is
         * not already bound.
         * \param s The shader
         * */
        void setShader(const std::shared_ptr<Shader> &s);
        /**
         * Sets the current shader to the null shader (0), and sets
         * the current shader to null (removes the ref)
         * */
        void clearShader();

        /**
         * Sets the viewport dimensions
         * \param w The width
         * \param h The height
         * */
        void setViewport(int w, int h);

        /**
         * \return The viewport width
         * */
        int getVPWidth() const;
        /**
         * \return The viewport height
         * */
        int getVPHeight() const;
        /**
         * \return The current shader
         * */
        Shader &getShader() const;
        /**
         * \return The engine
         * */
        Engine &getEngine() const;

        /**
         * Gets this class from its lua singleton
         * \param lua The current state
         * */
        static Context &fromLua(sol::state_view lua);
    };
}

#endif
