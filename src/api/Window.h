#ifndef DANZUN_API_WINDOW_H_INCLUDED
#define DANZUN_API_WINDOW_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan {
    class Window;
}

namespace dan::api {
    /**
     * Handle to the window singleton
     * */
    class Window {
        /// Handle to the window
        ::dan::Window *handle;
    public:
        /**
         * Create with window
         * \param handle The window
         * */
        Window(::dan::Window &handle);

        /**
         * Set the title of the window
         * \param text The title
         * */
        void setTitle(const std::string &text);
        /**
         * Set the window's size
         * \param width The width
         * \param height The height
         * */
        void setSize(int width, int height);
        /**
         * Set if the window is visible
         * \param toggle true if yes
         * */
        void setVisible(bool toggle);
        /**
         * Checkf if a key is pressed, based on its mapping in the engine singleton.
         * \param l The current state
         * \param name The name of the key
         * */
        bool keyDown(sol::this_state l, const std::string &name);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view lua);
    };
}

#endif
