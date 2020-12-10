#ifndef DANZUN_API_WINDOW_H_INCLUDED
#define DANZUN_API_WINDOW_H_INCLUDED

#include <map>

#include <sol/forward.hpp>

namespace dan {
    class Window;
}

namespace dan::api {
    class Window {
        ::dan::Window *handle;
        std::map<std::string, dan::keyt> keyMappings;
    public:
        Window(::dan::Window &handle);

        void setTitle(const std::string &text);
        void setSize(int width, int height);
        void setVisible(bool toggle);
        void keyDown(const std::string &name);

        static void open(sol::state_view &lua);
    }
}

#endif
