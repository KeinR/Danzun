#ifndef DANZUN_WINDOW_H_INCLUDED
#define DANZUN_WINDOW_H_INCLUDED

struct GLFWwindow;

namespace dan {
    class WindowEvent;
    class Cursor;
    class Color;
}

namespace dan {
    class Window {
    public:
        typedef GLFWwindow* handle_t;
    private:
        handle_t handle;
        void free();
        void steal(Window &other);
    public:

        enum inputMode {
            STICKY_KEYS,
            STICKY_MOUSE_BUTTONS,
            LOCK_KEYS_MODS,
            RAW_MOUSE_MOTION
        };
        enum cursorMode {
            CURSOR_NORMAL,
            CURSOR_HIDDEN,
            CURSOR_DISABLED
        };

        /**
        * Creates a window and makes itself the current context window
        */
        Window(const char *title, int width, int height, int MSAASamples);
        Window(Window &&other);
        ~Window();
        Window &operator=(Window &&other);

        void setCursor(const Cursor &cursor);
        void setDefaultCursor();

        void setCursorMode(cursorMode mode);
        void toggleInputMode(inputMode mode, bool toggle);

        void clearColorBuffer(const Color &color);
        void clearDepthBuffer();
        void clearStencilBuffer();
        void swapBuffers();
        void makeCurrent();
        void setEventCallback(WindowEvent &e);
        void clearEventCallback();

        void setShouldClose(bool value);
        bool shouldClose() const;

        const char *getClipboardString() const;
        void setClipboardString(const char *str);

        /**
        * Checks if the given key is pressed.
        * Takes a GLFW key enum constant.
        */
        bool keyPressed(int key) const;
        handle_t getHandle();

        float getMouseX() const;
        float getMouseY() const;
        void getMousePos(float &x, float &y) const;
        void setMousePos(float x, float y);

        int getWidth() const;
        int getHeight() const;
        void getSize(int &width, int &height) const;

        int getFramebufferWidth() const;
        int getFramebufferHeight() const;
        void getFramebufferSize(int &width, int &height) const;

        static void pollEvents();
        static void waitEvents();
        static void setVSyncLevel(int level);
    };
}

#endif
