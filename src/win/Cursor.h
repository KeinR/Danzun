#ifndef DANZUN_CURSOR_H_INCLUDED
#define DANZUN_CURSOR_H_INCLUDED

struct GLFWcursor;

namespace dan {
    class Cursor {
        GLFWcursor *handle;
        void steal(Cursor &other);
        void free();
    public:
        enum cursorType {
            ARROW,
            IBEAM,
            CROSSHAIR,
            HAND,
            HRESIZE,
            VRESIZE
        };

        Cursor();
        Cursor(cursorType type);
        Cursor(GLFWcursor *handle);
        Cursor(Cursor &&other);
        ~Cursor();

        Cursor &operator=(Cursor &&other);

        GLFWcursor *getHandle() const;
    };
}

#endif
