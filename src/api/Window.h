#ifndef DANZUN_API_WINDOW_H_INCLUDED
#define DANZUN_API_WINDOW_H_INCLUDED

#include <unordered_map>

#include <sol/sol.hpp>

#include "../win/enums.h"

namespace dan {
    class Window;
}

namespace dan::api {
    class Window {
        typedef std::unordered_map<std::string, dan::keyt> keyMappings_t;
        ::dan::Window *handle;
        keyMappings_t keyMappings;
    public:
        Window(::dan::Window &handle);

        void setTitle(const std::string &text);
        void setSize(int width, int height);
        void setVisible(bool toggle);
        bool keyDown(const std::string &name);

        static void open(sol::state_view lua);
    };
}

#endif
