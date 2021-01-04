#ifndef DANZUN_API_WINDOW_H_INCLUDED
#define DANZUN_API_WINDOW_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan {
    class Window;
}

namespace dan::api {
    class Window {
        ::dan::Window *handle;
    public:
        Window(::dan::Window &handle);

        void setTitle(const std::string &text);
        void setSize(int width, int height);
        void setVisible(bool toggle);
        bool keyDown(sol::this_state l, const std::string &name);

        static void open(sol::state_view lua);
    };
}

#endif
